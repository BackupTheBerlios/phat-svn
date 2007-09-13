/* 
 *
 * Most of this code comes from gAlan 0.2.0, copyright (C) 1999
 * Tony Garnock-Jones, with modifications by Sean Bolton,
 * copyright (c) 2004.  (gtkdial.c rolls over in its grave.)
 *
 * Phatised by Loki Davison.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307, USA.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtkmain.h>
#include <gtk/gtksignal.h>
#include "phatscrolloscope.h"

#if 0
#define SCROLL_DELAY_LENGTH     100
#define KNOB_SIZE               50
#endif

enum
{
    STATE_IDLE,         
    STATE_PRESSED,              
    STATE_DRAGGING,
    STATE_SCROLL,
};


/* properties */
enum
{
    PROP_0, /* oops, no props any more */
};

static void phat_scrolloscope_class_init         (PhatScrolloscopeClass *klass);
static void phat_scrolloscope_init               (PhatScrolloscope *knob);
static void phat_scrolloscope_destroy            (GtkObject *object);
static void phat_scrolloscope_realize            (GtkWidget *widget);
static void phat_scrolloscope_size_request       (GtkWidget *widget,
                                          GtkRequisition *requisition);
static gint phat_scrolloscope_expose             (GtkWidget *widget, 
                                          GdkEventExpose *event);
static gint phat_scrolloscope_button_press       (GtkWidget *widget, 
                                          GdkEventButton *event);
static gint phat_scrolloscope_button_release     (GtkWidget *widget,
                                          GdkEventButton *event);
static gint phat_scrolloscope_motion_notify      (GtkWidget *widget, 
                                          GdkEventMotion *event);
static gint phat_scrolloscope_scroll             (GtkWidget *widget, 
                                          GdkEventScroll *event);

static void phat_scrolloscope_set_property      (GObject *object, 
                                         guint prop_id, 
                                         const GValue *value, 
                                         GParamSpec   *pspec);
static void phat_scrolloscope_get_property      (GObject *object, 
                                         guint prop_id, 
                                         GValue *value, 
                                         GParamSpec *pspec);

//GError *gerror;


// Boiler Plate

G_DEFINE_TYPE (PhatScrolloscope, phat_scrolloscope, GTK_TYPE_DRAWING_AREA );

static void phat_scrolloscope_class_init (PhatScrolloscopeClass *klass) {
    GObjectClass     *g_object_class;
    GtkObjectClass   *object_class;
    GtkWidgetClass   *widget_class;

    object_class =   GTK_OBJECT_CLASS(klass);
    widget_class =   GTK_WIDGET_CLASS(klass);
    g_object_class = G_OBJECT_CLASS(klass);

    g_object_class->set_property = phat_scrolloscope_set_property;
    g_object_class->get_property = phat_scrolloscope_get_property;
    
    object_class->destroy =        phat_scrolloscope_destroy;

    widget_class->realize =        phat_scrolloscope_realize;
    widget_class->expose_event =   phat_scrolloscope_expose;
    widget_class->size_request =   phat_scrolloscope_size_request;
    widget_class->button_press_event = phat_scrolloscope_button_press;
    widget_class->button_release_event = phat_scrolloscope_button_release;
    widget_class->motion_notify_event = phat_scrolloscope_motion_notify;
    widget_class->scroll_event =   phat_scrolloscope_scroll;
}

static void phat_scrolloscope_init (PhatScrolloscope *scrollo) {

    GtkWidget *widget = GTK_WIDGET( scrollo );
    GdkColor bgcol;

    scrollo->zoomx = 5.0;
    scrollo->zoomy = 0.1;
    scrollo->stream = NULL;
    scrollo->dirty = FALSE;

    scrollo->smooth = 1000;
    //scrollo->diff_threshold = 0.02;
    scrollo->scroll = TRUE;
    scrollo->direction = GTK_DIR_DOWN;

    scrollo->saved_x = 0;
    scrollo->saved_y = 0;
    scrollo->state = STATE_IDLE;

    scrollo->current_pixel_pos = 0.0;
    scrollo->last_pixel_pos = 0.0;

    gdk_color_parse( "#000", &bgcol );
    gtk_widget_modify_bg( widget, GTK_STATE_NORMAL, &bgcol );

    gdk_color_parse( "#050", & (scrollo->col1) );
    gdk_color_parse( "#0b0", & (scrollo->col2) );
    gdk_color_parse( "#f00", & (scrollo->col3) );

    gdk_color_parse( "#555", & (scrollo->dcol1) );
    gdk_color_parse( "#cc0", & (scrollo->dcol2) );
    gdk_color_parse( "#aa0", & (scrollo->dcol3) );
}


// Create 

/**
 * phat_scrolloscope_new:
 * 
 * Returns: a newly created #PhatScrolloscope
 * 
 */

GtkWidget *phat_scrolloscope_new( GtkDirectionType dir ) {

    GObject *obj = g_object_new (PHAT_TYPE_SCROLLOSCOPE, NULL);
    GtkWidget *widget = GTK_WIDGET( obj );
    PhatScrolloscope *scrollo = PHAT_SCROLLOSCOPE( obj );
    scrollo->direction = dir;
    return widget;
}


// Overrides

static void phat_scrolloscope_destroy(GtkObject *object) {
    PhatScrolloscope *scrollo;

    g_return_if_fail(object != NULL);
    g_return_if_fail(PHAT_IS_SCROLLOSCOPE(object));

    scrollo = PHAT_SCROLLOSCOPE(object);

    if (GTK_OBJECT_CLASS(phat_scrolloscope_parent_class)->destroy)
        (*GTK_OBJECT_CLASS(phat_scrolloscope_parent_class)->destroy)(object);
}

static void phat_scrolloscope_realize(GtkWidget *widget) {
    //PhatScrolloscope *scrollo;

    g_return_if_fail(widget != NULL);
    g_return_if_fail(PHAT_IS_SCROLLOSCOPE(widget));

    if (GTK_WIDGET_CLASS(phat_scrolloscope_parent_class)->realize)
        (*GTK_WIDGET_CLASS(phat_scrolloscope_parent_class)->realize)(widget);

//    scrollo = PHAT_SCROLLOSCOPE(widget);
//    scrollo->scroll_pixmap = gdk_pixmap_new( widget->window, widget->allocation.width, widget->allocation.height, -1 );
#if 0
    scrollo->cx = gdk_cairo_create( scrollo->scroll_pixmap );
#endif
    //scrollo->cx = gdk_cairo_create( widget->window );

    gtk_widget_add_events( widget, GDK_BUTTON_PRESS_MASK | GDK_POINTER_MOTION_MASK | GDK_BUTTON_RELEASE_MASK ); 
}

static void phat_scrolloscope_size_request (GtkWidget *widget, GtkRequisition *requisition) {
    requisition->width = 100;
    requisition->height = 50;
}

static gint phat_scrolloscope_expose(GtkWidget *widget, GdkEventExpose *event) {
    PhatScrolloscope *scrollo;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_SCROLLOSCOPE(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

//    if (event->count > 0)
//        return FALSE;

    scrollo = PHAT_SCROLLOSCOPE(widget);
    
    cairo_t *cx = gdk_cairo_create( widget->window );

#if 0
    for( renderX = render_list; renderX; renderX = g_list_next( renderX ) ) {
	Renderer *rend = renderX->data;
	phat_wv_render( rend, cx, area, scrollo )
    }
#endif
    gdouble x1 = event->area.x-3;
    gdouble y1 = 0.0;
    gdouble x2 = event->area.x + event->area.width + 3;
    gdouble y2 = widget->allocation.height;

    gdouble w = widget->allocation.width;
    gdouble h = widget->allocation.height;
    
    GdkColor *color1 = & (scrollo->col1);
    GdkColor *color2 = & (scrollo->col2);
    GdkColor *color3 = & (scrollo->col3);
   // cairo_new_path( cx );
    
    if( scrollo->direction == GTK_DIR_DOWN ) {
	cairo_scale( cx, 1.0, -1.0 );
	cairo_translate( cx, 0, -h );
    }


    cairo_pattern_t *pat = cairo_pattern_create_linear( 0,0,0,h );
    cairo_pattern_add_color_stop_rgb( pat, 1.0,
	    color1->red/65536.0,
	    color1->green/65536.0,
	    color1->blue/65536.0 );
    cairo_pattern_add_color_stop_rgb( pat, 0.3,
	    color2->red/65536.0,
	    color2->green/65536.0,
	    color2->blue/65536.0 );
    cairo_pattern_add_color_stop_rgb( pat, 0.0,
	    color3->red/65536.0,
	    color3->green/65536.0,
	    color3->blue/65536.0 );
    cairo_set_source( cx, pat );

    int x;
    cairo_new_path( cx );
    cairo_move_to( cx, x1, y2);


    gfloat last_val = 0.0;
    gfloat *diffarray = g_alloca( sizeof(float) * (x2-x1+1) );
    for( x= x1; x<= x2; x++ ) {

	/*
	 * map screen position to sample position.
	 *
	 * sample_pos( x, zoom, pos ) 
	 *
	 * globals: audio_data, playhead
	 * render( cx, x1, x2 ) --->  render( cairo_t *cx, GtkRectangle area )
	 *
	 * globals: beat_data, playhead
	 *
	 *
	 */

//	gint samplepos = scrollo->stream->playpos + 

	/**
	 * ok. scrollo->current_pixel_pos
	 *     scrollo->last_pixel_pos
	 *
	 *
	 *
	 */
	gint samplepos = (gdouble)( scrollo->current_pixel_pos + x - w/2 )
		       * scrollo->zoomx * scrollo->stream->speed * 100.0;
	
	gfloat val = 0.0;
	if( samplepos >= 0 && samplepos < (scrollo->stream->len - 100*2) ) {
	    int i;
	    for( i=0; i<scrollo->smooth; i++ )
		val += powf( scrollo->stream->data[ (int) ( (samplepos + i)*2 ) ], 2.0 );

	    val /= (gfloat) scrollo->smooth;

	    cairo_line_to( cx, (gdouble) x, (1.0-val*scrollo->zoomy) * h );
	}
	diffarray[x-(int)x1]= val - last_val;
	last_val = val;
    }
    cairo_line_to( cx, x2, y2 );
    //cairo_line_to( cx, x1, y2 );

    cairo_close_path( cx );
    cairo_fill( cx );


    {
	GdkColor *color1 = & (scrollo->dcol1);
	GdkColor *color2 = & (scrollo->dcol2);
	GdkColor *color3 = & (scrollo->dcol3);
	cairo_pattern_t *pat = cairo_pattern_create_linear( 0,0,0,h );
	cairo_pattern_add_color_stop_rgba( pat, 0.0,
		color1->red/65536.0,
		color1->green/65536.0,
		color1->blue/65536.0,
		0.9);
	cairo_pattern_add_color_stop_rgba( pat, 0.1,
		color2->red/65536.0,
		color2->green/65536.0,
		color2->blue/65536.0,
		0.9);
	cairo_pattern_add_color_stop_rgba( pat, 1.0,
		color3->red/65536.0,
		color3->green/65536.0,
		color3->blue/65536.0,
		0.9);
	cairo_set_source( cx, pat );
    }
    cairo_new_path( cx );
    cairo_move_to( cx, x1,y1 );

    for( x= x1; x<= x2; x++ ) {
	gfloat val = diffarray[x-(int)x1];
	if( val > 0.03 )
	    val += 0.5;
	cairo_line_to( cx, (gdouble) x, (val*scrollo->zoomy) * h );
    }

    cairo_line_to( cx, x2, y1 );
    cairo_close_path( cx );
    cairo_fill( cx );


    cairo_destroy( cx );

    scrollo->scroll = TRUE;


    return FALSE;
}

static gint phat_scrolloscope_button_press(GtkWidget *widget, GdkEventButton *event) {
    PhatScrolloscope *scrollo;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_SCROLLOSCOPE(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    scrollo = PHAT_SCROLLOSCOPE(widget);

    scrollo->state = STATE_PRESSED;
    scrollo->saved_x = event->x;
    scrollo->saved_y = event->y;
    gtk_grab_add(widget); 

    return FALSE;
}

static gint phat_scrolloscope_button_release(GtkWidget *widget, GdkEventButton *event) {
    PhatScrolloscope *scrollo;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_SCROLLOSCOPE(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    scrollo = PHAT_SCROLLOSCOPE(widget);

    printf( "release\n" );
    scrollo->state = STATE_IDLE;
    gtk_grab_remove(widget);
    scrollo->stream->tmp_speed = 0.0;

    return FALSE;
}

static gint phat_scrolloscope_motion_notify(GtkWidget *widget, GdkEventMotion *event) {
    PhatScrolloscope *scrollo;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_SCROLLOSCOPE(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    scrollo = PHAT_SCROLLOSCOPE(widget);

    if( scrollo->state == STATE_PRESSED ) {
	scrollo->state = STATE_DRAGGING;
    }
    
    if( scrollo->state == STATE_DRAGGING ) {
	gdouble diff = (event->x - scrollo->saved_x);
	scrollo->stream->tmp_speed = diff *0.001;
    }

    return FALSE;
}

static gint phat_scrolloscope_scroll (GtkWidget *widget, GdkEventScroll *event) {
    return TRUE;
}


// Public Methods

void phat_scrolloscope_update( PhatScrolloscope *scrollo ) {

    g_return_if_fail(scrollo != NULL );
    g_return_if_fail(PHAT_IS_SCROLLOSCOPE(scrollo) );

    GtkWidget *widget = GTK_WIDGET( scrollo );

    if( scrollo->stream->speed != scrollo->last_speed ) {
	scrollo->last_speed = scrollo->stream->speed;
	scrollo->current_pixel_pos = (gint) (scrollo->stream->pos_est / scrollo->zoomx /100.0);
	scrollo->last_pixel_pos = scrollo->current_pixel_pos;
	scrollo->scroll = FALSE;
	gdk_window_invalidate_rect( GTK_WIDGET( scrollo )->window, NULL, 0 );

    } else if( scrollo->dirty ) {
	scrollo->dirty = FALSE;
	scrollo->current_pixel_pos = (gint) (scrollo->stream->pos_est / scrollo->zoomx /100.0);
	scrollo->last_pixel_pos = scrollo->current_pixel_pos;
	scrollo->scroll = FALSE;
	gdk_window_invalidate_rect( GTK_WIDGET( scrollo )->window, NULL, 0 );
    } else {
	if( scrollo->scroll ) {
	    //gint diff = (scrollo->last_pos - scrollo->stream->playpos) / scrollo->zoomx / 100.0;
	    scrollo->current_pixel_pos = (gint) (scrollo->stream->pos_est / scrollo->zoomx /100.0);
	    gint diff = (scrollo->last_pixel_pos - scrollo->current_pixel_pos);
	    scrollo->last_pixel_pos = scrollo->current_pixel_pos;

	    if( diff ) 
		gdk_window_scroll( widget->window, diff, 0 );
	}
    }
}

void phat_scrolloscope_set_audio_stream( PhatScrolloscope *scrollo, PhatAudiostream *audio_stream ) {

    g_return_if_fail(scrollo != NULL );
    g_return_if_fail(PHAT_IS_SCROLLOSCOPE(scrollo) );

    scrollo->stream = audio_stream;
}


// Properties
static void
phat_scrolloscope_set_property (GObject      *object, 
                        guint         prop_id, 
                        const GValue *value, 
                        GParamSpec   *pspec)
{
    //PhatScrolloscope *knob = PHAT_KNOB (object);

    switch (prop_id) 
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
phat_scrolloscope_get_property (GObject    *object, 
                        guint       prop_id, 
                        GValue     *value, 
                        GParamSpec *pspec)
{
    //PhatScrolloscope *knob = PHAT_KNOB (object);
    
    switch (prop_id) 
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}



