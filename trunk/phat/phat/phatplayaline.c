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
#include "phatplayaline.h"

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

static void phat_playaline_class_init         (PhatPlayalineClass *klass);
static void phat_playaline_init               (PhatPlayaline *knob);
static void phat_playaline_destroy            (GtkObject *object);
//static void phat_playaline_realize            (GtkWidget *widget);
static void phat_playaline_size_request       (GtkWidget *widget,
                                          GtkRequisition *requisition);
static gint phat_playaline_expose             (GtkWidget *widget, 
                                          GdkEventExpose *event);
static gint phat_playaline_button_press       (GtkWidget *widget, 
                                          GdkEventButton *event);
static gint phat_playaline_button_release     (GtkWidget *widget,
                                          GdkEventButton *event);
static gint phat_playaline_motion_notify      (GtkWidget *widget, 
                                          GdkEventMotion *event);
static gint phat_playaline_scroll             (GtkWidget *widget, 
                                          GdkEventScroll *event);

static void phat_playaline_set_property      (GObject *object, 
                                         guint prop_id, 
                                         const GValue *value, 
                                         GParamSpec   *pspec);
static void phat_playaline_get_property      (GObject *object, 
                                         guint prop_id, 
                                         GValue *value, 
                                         GParamSpec *pspec);

GError *gerror;

/* global pixbufs for less mem usage */

/* Local data */

G_DEFINE_TYPE (PhatPlayaline, phat_playaline, GTK_TYPE_DRAWING_AREA );

static void phat_playaline_class_init (PhatPlayalineClass *klass) {
    GObjectClass     *g_object_class;
    GtkObjectClass   *object_class;
    GtkWidgetClass   *widget_class;

    object_class =   GTK_OBJECT_CLASS(klass);
    widget_class =   GTK_WIDGET_CLASS(klass);
    g_object_class = G_OBJECT_CLASS(klass);

    g_object_class->set_property = phat_playaline_set_property;
    g_object_class->get_property = phat_playaline_get_property;
    
    object_class->destroy =        phat_playaline_destroy;

//    widget_class->realize =        phat_playaline_realize;
    widget_class->expose_event =   phat_playaline_expose;
    widget_class->size_request =   phat_playaline_size_request;
    widget_class->button_press_event = phat_playaline_button_press;
    widget_class->button_release_event = phat_playaline_button_release;
    widget_class->motion_notify_event = phat_playaline_motion_notify;
    widget_class->scroll_event =   phat_playaline_scroll;
}

static void phat_playaline_init (PhatPlayaline *playaline) {

    GtkWidget *widget = GTK_WIDGET( playaline );
    GdkColor bgcol;

    playaline->stream = NULL;

    playaline->direction = GTK_DIR_UP;

    gdk_color_parse( "#000", &bgcol );
    gtk_widget_modify_bg( widget, GTK_STATE_NORMAL, &bgcol );

    gdk_color_parse( "#555", & (playaline->col1) );
    gdk_color_parse( "#fff", & (playaline->col2) );
    gdk_color_parse( "#f5f", & (playaline->col3) );

    gdk_color_parse( "#50c", & (playaline->dcol1) );
    gdk_color_parse( "#005", & (playaline->dcol2) );
    gdk_color_parse( "#50c", & (playaline->dcol3) );
}


/**
 * phat_playaline_new:
 * 
 * Returns: a newly created #PhatPlayaline
 * 
 */
GtkWidget *phat_playaline_new( GtkDirectionType dir) {

    GObject *obj = g_object_new (PHAT_TYPE_PLAYALINE, NULL);
    GtkWidget *widget = GTK_WIDGET( obj );
    PhatPlayaline *pline = PHAT_PLAYALINE( obj );

    pline->direction = dir;

    return widget;
}



static void phat_playaline_destroy(GtkObject *object) {
    PhatPlayaline *playaline;

    g_return_if_fail(object != NULL);
    g_return_if_fail(PHAT_IS_PLAYALINE(object));

    playaline = PHAT_PLAYALINE(object);

    if (GTK_OBJECT_CLASS(phat_playaline_parent_class)->destroy)
        (*GTK_OBJECT_CLASS(phat_playaline_parent_class)->destroy)(object);
}



static void phat_playaline_size_request (GtkWidget *widget, GtkRequisition *requisition)
{
    requisition->width = 100;
    requisition->height = 15;
}

static gint phat_playaline_expose(GtkWidget *widget, GdkEventExpose *event)
{
    PhatPlayaline *playaline;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_PLAYALINE(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

//    if (event->count > 0)
//        return FALSE;

    playaline = PHAT_PLAYALINE(widget);

    cairo_t *cx = gdk_cairo_create( widget->window );
#if 0
    for( renderX = render_list; renderX; renderX = g_list_next( renderX ) ) {
	Renderer *rend = renderX->data;
	phat_wv_render( rend, cx, area, playaline )
    }
#endif
    //gdouble x1 = widget->allocation.x;
    //gdouble y1 = widget->allocation.y;
    gdouble x1 = 0.0;
    gdouble y1 = 0.0;

    gdouble w = widget->allocation.width;
    gdouble h = widget->allocation.height;

    gdouble x2 = x1+w;
    gdouble y2 = y1+h;
    
    printf( "x1=%f y1=%f x2=%f y2=%f\n", (float)x1,(float)y1, (float)x2, (float)y2 );

    GdkColor *color1 = & (playaline->col1);
    GdkColor *color2 = & (playaline->col2);
    GdkColor *color3 = & (playaline->col3);
   // cairo_new_path( cx );
    

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
    //cairo_set_source_rgb( cx, 1.0, 1.0, 1.0 );

    if( playaline->direction == GTK_DIR_UP ) {
	cairo_new_path( cx );
	cairo_move_to( cx, x1+w/2-5, y2);
	cairo_line_to( cx, x1+w/2, y1);
	cairo_line_to( cx, x1+w/2+5, y2);
	cairo_close_path( cx );
	cairo_fill( cx );
    } else {
	cairo_new_path( cx );
	cairo_move_to( cx, x1+w/2-5, y1);
	cairo_line_to( cx, x1+w/2, y2);
	cairo_line_to( cx, x1+w/2+5, y1);
	cairo_close_path( cx );
	cairo_fill( cx );
    }

#if 1

    {
	GdkColor *color1 = & (playaline->dcol1);
	GdkColor *color2 = & (playaline->dcol2);
	GdkColor *color3 = & (playaline->dcol3);
	cairo_pattern_t *pat = cairo_pattern_create_linear( 0,0,w,h/2 );
	cairo_pattern_add_color_stop_rgba( pat, 0.0,
		color1->red/65536.0,
		color1->green/65536.0,
		color1->blue/65536.0,
		0.5);
	cairo_pattern_add_color_stop_rgba( pat, 0.5,
		color2->red/65536.0,
		color2->green/65536.0,
		color2->blue/65536.0,
		0.3);
	cairo_pattern_add_color_stop_rgba( pat, 1.0,
		color3->red/65536.0,
		color3->green/65536.0,
		color3->blue/65536.0,
		0.5);
	cairo_set_source( cx, pat );
    }
    cairo_rectangle( cx, x1, y1+h/8,w,h-h/4 );
    cairo_fill( cx );

#endif

    cairo_destroy( cx );


    return FALSE;
}

static gint phat_playaline_button_press(GtkWidget *widget, GdkEventButton *event) {
    PhatPlayaline *playaline;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_PLAYALINE(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    playaline = PHAT_PLAYALINE(widget);

    return FALSE;
}

static gint phat_playaline_button_release(GtkWidget *widget, GdkEventButton *event) {
    PhatPlayaline *playaline;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_PLAYALINE(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    playaline = PHAT_PLAYALINE(widget);

    return FALSE;
}

static gint phat_playaline_motion_notify(GtkWidget *widget, GdkEventMotion *event) {
    PhatPlayaline *playaline;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_PLAYALINE(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    playaline = PHAT_PLAYALINE(widget);

    return FALSE;
}

static gint phat_playaline_scroll (GtkWidget *widget, GdkEventScroll *event)
{
    return TRUE;
}

void phat_playaline_update( PhatPlayaline *playaline ) {

    g_return_if_fail(playaline != NULL );
    g_return_if_fail(PHAT_IS_PLAYALINE(playaline) );

    //GtkWidget *widget = GTK_WIDGET( playaline );
}

void phat_playaline_set_audio_stream( PhatPlayaline *playaline, PhatAudiostream *audio_stream ) {

    g_return_if_fail(playaline != NULL );
    g_return_if_fail(PHAT_IS_PLAYALINE(playaline) );

    playaline->stream = audio_stream;
}

static void
phat_playaline_set_property (GObject      *object, 
                        guint         prop_id, 
                        const GValue *value, 
                        GParamSpec   *pspec)
{
    //PhatPlayaline *knob = PHAT_KNOB (object);

    switch (prop_id) 
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
phat_playaline_get_property (GObject    *object, 
                        guint       prop_id, 
                        GValue     *value, 
                        GParamSpec *pspec)
{
    //PhatPlayaline *knob = PHAT_KNOB (object);
    
    switch (prop_id) 
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}
