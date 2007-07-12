/*
 *
 *  Slider for Phat. Copyright (C) 2007 Loki Davison.
 *  Ported from Ardour, original version by Paul Davis, designed by Thorsten Wilms.
 *
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtkmain.h>
#include <gtk/gtksignal.h>
#include "phatslider.h"

enum
{
    STATE_IDLE,         
    STATE_PRESSED,              
    STATE_DRAGGING,
    STATE_SCROLL,
};

/* signals */
enum
{
    VALUE_CHANGED_SIGNAL,
    CHANGED_SIGNAL,
    LAST_SIGNAL,
};

static int signals[LAST_SIGNAL];
static void phat_slider_class_init(PhatSliderClass *klass);
static void phat_slider_init(PhatSlider *slider);
//static void phat_slider_destroy(GtkObject *object);
static void phat_slider_realize(GtkWidget *widget);
static void phat_slider_size_request(GtkWidget *widget, GtkRequisition *requisition);
//static void phat_slider_size_allocate(GtkWidget *widget, GtkAllocation *allocation);
static gint phat_slider_expose(GtkWidget *widget, GdkEventExpose *event);
static gint phat_slider_button_press(GtkWidget *widget, GdkEventButton *event);
static gint phat_slider_button_release(GtkWidget *widget, GdkEventButton *event);
static gint phat_slider_motion_notify(GtkWidget *widget, GdkEventMotion *event);
static gint phat_slider_scroll (GtkWidget *widget, GdkEventScroll *event);
//static void phat_slider_update(PhatSlider *slider);
static void phat_slider_adjustment_changed(GtkAdjustment *adjustment, gpointer data);
static int phat_slider_display_height (GtkWidget *widget);


#define PIXMAPDIRIFY(filename) \
		(SITE_PKGDATA_DIR G_DIR_SEPARATOR_S "pixmaps" G_DIR_SEPARATOR_S filename)

/* Local data */

static GtkWidgetClass *parent_class = NULL;

GType phat_slider_get_type(void) 
{
    static GType slider_type = 0;

    if (!slider_type) {
        static const GTypeInfo info = 
            {
                sizeof (PhatSliderClass),
                NULL,
                NULL,
                (GClassInitFunc) phat_slider_class_init,
                NULL,
                NULL,
                sizeof (PhatSlider),
                0,
                (GInstanceInitFunc) phat_slider_init,
            };

        slider_type =  g_type_register_static (GTK_TYPE_WIDGET,
                                             "PhatSlider",
                                             &info,
                                             0);
    }

    return slider_type;
}

static void phat_slider_class_init (PhatSliderClass *class) {
    GtkObjectClass *object_class;
    GtkWidgetClass *widget_class;

    object_class = (GtkObjectClass*) class;
    widget_class = (GtkWidgetClass*) class;

    parent_class = gtk_type_class(gtk_widget_get_type());

    //object_class->destroy = phat_slider_destroy;

    widget_class->realize = phat_slider_realize;
    widget_class->expose_event = phat_slider_expose;
    widget_class->size_request = phat_slider_size_request;
    //widget_class->size_allocate = phat_slider_size_allocate;
    widget_class->button_press_event = phat_slider_button_press;
    widget_class->button_release_event = phat_slider_button_release;
    widget_class->motion_notify_event = phat_slider_motion_notify;
    widget_class->scroll_event = phat_slider_scroll;

    /**
     * PhatSlider::value-changed:
     * @slider: the object on which the signal was emitted
     *
     * The "value-changed" signal is emitted when the value of the
     * sliderbutton's adjustment changes.
     *
     */
    signals[VALUE_CHANGED_SIGNAL] =
        g_signal_new ("value-changed",
                      G_TYPE_FROM_CLASS (class),
                      G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
                      G_STRUCT_OFFSET (PhatSliderClass, value_changed),
                      NULL, NULL,
                      g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
    class->value_changed = NULL;
}

static void phat_slider_init (PhatSlider *slider) {
    slider->pixbuf = NULL;
    slider->adjustment = NULL;
}

GtkWidget * phat_slider_new (GtkAdjustment* adjustment)
{
        PhatSlider *slider;
	GError *error = NULL;

	slider = gtk_type_new(phat_slider_get_type());
	slider->dragging = FALSE;
	slider->default_value = adjustment->value;
	slider->last_drawn = -1;
	slider->pixbuf = gdk_pixbuf_new_from_file( PIXMAPDIRIFY( "fader_belt.png" ), &error);
	slider->pixheight = gdk_pixbuf_get_height(slider->pixbuf);
	slider->adjustment = adjustment;


	slider->view.x = 0;
	slider->view.y = 0;
	slider->view.width =  gdk_pixbuf_get_width(slider->pixbuf);
	slider->view.height = slider->pixheight / 2;

	slider->unity_y = (int) rint (slider->view.height - (slider->default_value * slider->view.height)) - 1;
	
	gtk_signal_connect(
        GTK_OBJECT(slider->adjustment),
        "changed",
        GTK_SIGNAL_FUNC(phat_slider_adjustment_changed),
        (gpointer)slider);
    gtk_signal_connect(
        GTK_OBJECT(slider->adjustment),
        "value_changed",
        GTK_SIGNAL_FUNC(phat_slider_adjustment_changed),
        (gpointer)slider);

	//add_events (Gdk::BUTTON_PRESS_MASK|Gdk::BUTTON_RELEASE_MASK|Gdk::POINTER_MOTION_MASK|Gdk::SCROLL_MASK);
	return GTK_WIDGET(slider);
}

static void phat_slider_realize(GtkWidget *widget)
{
    PhatSlider *slider;
    GdkWindowAttr attributes;
    gint attributes_mask;
    //extern GdkPixbuf **pixbuf;

    g_return_if_fail(widget != NULL);
    g_return_if_fail(PHAT_IS_SLIDER(widget));

    GTK_WIDGET_SET_FLAGS(widget, GTK_REALIZED);
    slider = PHAT_SLIDER(widget);

    attributes.x = widget->allocation.x;
    attributes.y = widget->allocation.y;
    attributes.width = slider->view.width;
    attributes.height = slider->view.width;
    attributes.wclass = GDK_INPUT_OUTPUT;
    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.event_mask =
        gtk_widget_get_events (widget) | 
        GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK | 
        GDK_BUTTON_RELEASE_MASK | GDK_BUTTON_MOTION_MASK |
        GDK_SCROLL_MASK;
    attributes.visual = gtk_widget_get_visual(widget);
    attributes.colormap = gtk_widget_get_colormap(widget);

    attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
    widget->window = gdk_window_new(widget->parent->window, &attributes, attributes_mask);

    widget->style = gtk_style_attach(widget->parent->style, widget->window);

    gdk_window_set_user_data(widget->window, widget);
    
    gtk_style_set_background(widget->style, widget->window, GTK_STATE_NORMAL);


    //knob->mask_gc = gdk_gc_new(widget->window);
    //gdk_gc_copy(knob->mask_gc, widget->style->bg_gc[GTK_STATE_NORMAL]);
    //gdk_gc_set_clip_mask(knob->mask_gc, knob->mask);

}



static gint phat_slider_expose(GtkWidget *widget, GdkEventExpose *event) {
    PhatSlider *slider;
    int dh, offset_into_pixbuf;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_SLIDER(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    if (event->count > 0)
        return FALSE;

    slider = PHAT_SLIDER(widget);

    GdkRectangle intersection;

    dh = phat_slider_display_height (widget);
    offset_into_pixbuf = (int) floor (slider->view.height / ((float) slider->view.height / dh));

    if (gdk_rectangle_intersect (&(slider->view), &event->area, &intersection)) {
	


	gdk_draw_pixbuf(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], slider->pixbuf, 
				       intersection.x, offset_into_pixbuf + intersection.y,
				       intersection.x, intersection.y,
				       intersection.width, intersection.height,
				       GDK_RGB_DITHER_NONE, 0, 0);

	gdk_draw_line (widget->window, widget->style->bg_gc[GTK_STATE_ACTIVE], 0, 0, slider->view.width - 1, 0); /* top */
	gdk_draw_line (widget->window, widget->style->bg_gc[GTK_STATE_ACTIVE], 0, 0, 0, slider->view.height - 1); /* left */
	gdk_draw_line (widget->window, widget->style->bg_gc[GTK_STATE_NORMAL], slider->view.width - 1, 0, slider->view.width - 1, slider->view.height - 1); /* right */
	gdk_draw_line (widget->window, widget->style->bg_gc[GTK_STATE_NORMAL], 0,  slider->view.height - 1, slider->view.width - 1, slider->view.height - 1); /* bottom */
    }

    /* always draw the line */

    gdk_draw_line (widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], 1, slider->unity_y, slider->view.width - 2, slider->unity_y);

    slider->last_drawn = dh;
    return FALSE;

}

static void phat_slider_size_request (GtkWidget *widget, GtkRequisition *requisition) 
{
    PhatSlider *slider;

    slider = PHAT_SLIDER(widget);

    requisition->width = slider->view.width;
    requisition->height = slider->view.height;
}

gint
phat_slider_button_press (GtkWidget *widget, GdkEventButton* ev)
{
    PhatSlider *slider;

    slider = PHAT_SLIDER(widget);
    switch (ev->button) {
    case 1:
    case 2:
	    //add_modal_grab(); #FIXME is this in gtk? or just gtkmm?...
	    slider->grab_y = ev->y;
	    slider->grab_start = ev->y;
	    slider->grab_window = ev->window;
	    slider->dragging = TRUE;
	    break;
    default:
	    break;
    } 
			   

    return FALSE;
}

gint
phat_slider_button_release (GtkWidget *widget, GdkEventButton* ev)
{
	PhatSlider *slider;

	slider = PHAT_SLIDER(widget);

	double fract;
	
	switch (ev->button) {
	case 1:
		if (slider->dragging) {
			//remove_modal_grab();
			slider->dragging = FALSE;

			if (ev->y == slider->grab_start) {

				/* no motion - just a click */

				if (ev->state & GDK_SHIFT_MASK) {
					gtk_adjustment_set_value(slider->adjustment, slider->default_value);
				} else if (ev->state & GDK_CONTROL_MASK) {
					gtk_adjustment_set_value(slider->adjustment, slider->adjustment->lower);
				} else if (ev->y < slider->view.height - phat_slider_display_height(widget)) {
					/* above the current display height, remember X Window coords */
					gtk_adjustment_set_value(slider->adjustment, slider->adjustment->value + 
						slider->adjustment->step_increment);
				} else {
				    gtk_adjustment_set_value(slider->adjustment, slider->adjustment->value - 
						slider->adjustment->step_increment);
				}
			}

		} 
		break;
		
	case 2:
		if (slider->dragging) {
			//remove_modal_grab();
			slider->dragging = FALSE;
			
			fract = 1.0 - (ev->y / slider->view.height); // inverted X Window coordinates, grrr
			
			fract = fmin(1.0, fract);
			fract = fmax(0.0, fract);
			
			gtk_adjustment_set_value(slider->adjustment, (fract * (slider->adjustment->lower - slider->adjustment->upper)));
		}
		break;

	default:
		break;
	}

	return FALSE;
}

gint
phat_slider_scroll (GtkWidget *widget, GdkEventScroll* ev)
{
    	PhatSlider *slider;

	slider = PHAT_SLIDER(widget);

	double scale;
	
	if (ev->state & GDK_CONTROL_MASK) {
		if (ev->state & GDK_MOD1_MASK) {
			scale = 0.05;
		} else {
			scale = 0.1;
		}
	} else {
		scale = 0.5;
	}

	switch (ev->direction) {

	case GDK_SCROLL_UP:
		/* wheel up */
		gtk_adjustment_set_value(slider->adjustment, slider->adjustment->value + 
						(slider->adjustment->page_increment * scale));
		break;
	case GDK_SCROLL_DOWN:
		/* wheel down */
		gtk_adjustment_set_value(slider->adjustment, slider->adjustment->value - 
						(slider->adjustment->page_increment * scale));
		break;
	default:
		break;
	}
	return FALSE;
}

gint
phat_slider_motion_notify (GtkWidget *widget, GdkEventMotion* ev)
{
        PhatSlider *slider;

	slider = PHAT_SLIDER(widget);

	if (slider->dragging) {
		double fract;
		double delta;
		double scale;

		if (ev->window != slider->grab_window) {
			slider->grab_y = ev->y;
			slider->grab_window = ev->window;
			return TRUE;
		}
		
		if (ev->state & GDK_CONTROL_MASK) {
			if (ev->state & GDK_MOD1_MASK) {
				scale = 0.05;
			} else {
				scale = 0.1;
			}
		} else {
			scale = 1.0;
		}

		delta = ev->y - slider->grab_y;
		slider->grab_y = ev->y;

		fract = (delta / slider->view.height);

		fract = fmin (1.0, fract);
		fract = fmax (-1.0, fract);

		// X Window is top->bottom for 0..Y
		
		fract = -fract;
		gtk_adjustment_set_value(slider->adjustment, slider->adjustment->value + scale * fract * 
			(slider->adjustment->upper - slider->adjustment->lower));

	}

	return TRUE;
}

static void
phat_slider_adjustment_changed (GtkAdjustment *adjustment, gpointer data)
{
        PhatSlider *slider;

	slider = PHAT_SLIDER(data);

	if (phat_slider_display_height(GTK_WIDGET(slider)) != slider->last_drawn) {
		gtk_widget_draw(GTK_WIDGET(slider), NULL);
	}
}

static int
phat_slider_display_height (GtkWidget *widget)
{       
	PhatSlider *slider;
	double fract;

	slider = PHAT_SLIDER(widget);

	fract = (slider->adjustment->upper - slider->adjustment->value) / (slider->adjustment->upper - slider->adjustment->lower);
	return (int) floor (slider->view.height * (1.0 - fract));
}

