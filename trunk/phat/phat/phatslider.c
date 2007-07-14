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
#include <gtk/gtkrange.h>
#include "phatslider.h"

enum
{
    STATE_IDLE,         
    STATE_PRESSED,              
    STATE_DRAGGING,
    STATE_SCROLL,
};


static void phat_slider_class_init(PhatSliderClass *klass);
static void phat_slider_init(PhatSlider *slider);
//static void phat_slider_destroy(GtkObject *object);
//static void phat_slider_realize(GtkWidget *widget);
static void phat_slider_size_request(GtkWidget *widget, GtkRequisition *requisition);
//static void phat_slider_size_allocate(GtkWidget *widget, GtkAllocation *allocation);
static gint phat_slider_expose(GtkWidget *widget, GdkEventExpose *event);
static gint phat_slider_button_press(GtkWidget *widget, GdkEventButton *event);
static gint phat_slider_button_release(GtkWidget *widget, GdkEventButton *event);
static gint phat_slider_motion_notify(GtkWidget *widget, GdkEventMotion *event);
static gint phat_slider_scroll (GtkWidget *widget, GdkEventScroll *event);
//static void phat_slider_update(PhatSlider *slider);
//static void phat_slider_adjustment_changed(GtkAdjustment *adjustment, gpointer data);
static int phat_slider_display_height (GtkWidget *widget);


#define PIXMAPDIRIFY(filename) \
		(SITE_PKGDATA_DIR G_DIR_SEPARATOR_S "pixmaps" G_DIR_SEPARATOR_S filename)

/* Local data */

G_DEFINE_TYPE(PhatSlider, phat_slider, GTK_TYPE_RANGE);

GdkPixbuf *fader_belt = NULL;

static void phat_slider_class_init (PhatSliderClass *klass) {
    GObjectClass   *g_object_class;
    GtkObjectClass *object_class;
    GtkWidgetClass *widget_class;

    g_object_class = G_OBJECT_CLASS (klass);
    object_class = GTK_OBJECT_CLASS (klass);
    widget_class = GTK_WIDGET_CLASS (klass);

    widget_class->expose_event =         phat_slider_expose;
    widget_class->size_request =         phat_slider_size_request;
    //widget_class->size_allocate =      phat_slider_size_allocate;
    widget_class->button_press_event =   phat_slider_button_press;
    widget_class->button_release_event = phat_slider_button_release;
    widget_class->motion_notify_event =  phat_slider_motion_notify;
    widget_class->scroll_event =         phat_slider_scroll;

}

static void phat_slider_init (PhatSlider *slider)
{    
    GTK_WIDGET_SET_FLAGS (GTK_WIDGET(slider), GTK_NO_WINDOW);
    
    slider->dragging = FALSE;
	slider->view.x = 0;
	slider->view.y = 0;
	slider->last_drawn = -1;
    
    if (fader_belt == NULL)
        fader_belt = gdk_pixbuf_new_from_file( PIXMAPDIRIFY( "fader_belt.png" ), NULL);  
    slider->pixbuf = fader_belt;    
    
    slider->pixheight = gdk_pixbuf_get_height(slider->pixbuf);
	slider->view.width =  gdk_pixbuf_get_width(slider->pixbuf);
	slider->view.height = slider->pixheight / 2;
    slider->unity_y = (int) rint (slider->view.height - (slider->default_value * slider->view.height)) - 1;
    
    /* warning, slider->default_value is not set at the moment */
}

GtkWidget * phat_slider_new (GtkAdjustment* adjustment)
{

    return g_object_new (PHAT_TYPE_SLIDER,
                          "adjustmnet",
                           adjustment,
                           NULL);
}

GtkWidget* phat_slider_new_with_range (double value,
                                       double lower,
                                       double upper,
                                       double step)
{
    GtkAdjustment *adj;
    
    adj = (GtkAdjustment *)gtk_adjustment_new(value, lower, upper, step, step, 0);
    
    return phat_slider_new(adj);
    
}

static gint phat_slider_expose(GtkWidget *widget, GdkEventExpose *event) {
    PhatSlider *slider;
    int dh, offset_into_pixbuf;
    GdkRectangle expose_area;

    g_return_val_if_fail(widget != NULL, FALSE);
    g_return_val_if_fail(PHAT_IS_SLIDER(widget), FALSE);
    g_return_val_if_fail(event != NULL, FALSE);

    if (event->count > 0)
        return FALSE;

    slider = PHAT_SLIDER(widget);

    GdkRectangle intersection;

    expose_area = event->area;
    expose_area.x -= widget->allocation.x;
    expose_area.y -= widget->allocation.y;

    dh = phat_slider_display_height (widget);
    offset_into_pixbuf = (int) floor (slider->view.height / ((float) slider->view.height / dh));

    if (gdk_rectangle_intersect (&(slider->view), &expose_area, &intersection)) {
	
    //printf ("x %d y %d\n", widget->allocation.x, widget->allocation.y);

	gdk_draw_pixbuf(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], slider->pixbuf, 
				       intersection.x, offset_into_pixbuf + intersection.y,
				       intersection.x + widget->allocation.x, intersection.y + widget->allocation.y,
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
	    gtk_grab_add(widget);
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
    GtkRange   *range;

	slider = PHAT_SLIDER(widget);
    range  = GTK_RANGE(widget);

	double fract;
	
	switch (ev->button) {
	case 1:
		if (slider->dragging) {
			gtk_grab_remove(widget);
			slider->dragging = FALSE;

			if (ev->y == slider->grab_start) {

				/* no motion - just a click */

				if (ev->state & GDK_SHIFT_MASK) {
					gtk_adjustment_set_value(range->adjustment, slider->default_value);
				} else if (ev->state & GDK_CONTROL_MASK) {
					gtk_adjustment_set_value(range->adjustment, range->adjustment->lower);
				} else if (ev->y < slider->view.height - phat_slider_display_height(widget)) {
					/* above the current display height, remember X Window coords */
					gtk_adjustment_set_value(range->adjustment, range->adjustment->value + 
						range->adjustment->step_increment);
				} else {
				    gtk_adjustment_set_value(range->adjustment, range->adjustment->value - 
						range->adjustment->step_increment);
				}
			}

		} 
		break;
		
	case 2:
		if (slider->dragging) {
			gtk_grab_remove(widget);
			slider->dragging = FALSE;
			
			fract = 1.0 - (ev->y / slider->view.height); // inverted X Window coordinates, grrr
			
			fract = fmin(1.0, fract);
			fract = fmax(0.0, fract);
			
			gtk_adjustment_set_value(range->adjustment, (fract * (range->adjustment->lower - range->adjustment->upper)));
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
    GtkRange   *range;
    
	slider = PHAT_SLIDER(widget);
    range  = GTK_RANGE(widget);
    
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
		gtk_adjustment_set_value(range->adjustment, range->adjustment->value + 
						(range->adjustment->page_increment * scale));
		break;
	case GDK_SCROLL_DOWN:
		/* wheel down */
		gtk_adjustment_set_value(range->adjustment, range->adjustment->value - 
						(range->adjustment->page_increment * scale));
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
    GtkRange   *range;

	slider = PHAT_SLIDER(widget);
    range  = GTK_RANGE(widget);

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
        gtk_adjustment_set_value(range->adjustment, range->adjustment->value + scale * fract * 
        (range->adjustment->upper - range->adjustment->lower));

	}

	return TRUE;
}

#if 0
static void
phat_slider_adjustment_changed (GtkAdjustment *adjustment, gpointer data)
{
    PhatSlider *slider;

    slider = PHAT_SLIDER(data);

    if (phat_slider_display_height(GTK_WIDGET(slider)) != slider->last_drawn) {
        gtk_widget_draw(GTK_WIDGET(slider), NULL);
    }
}

#endif
static int
phat_slider_display_height (GtkWidget *widget)
{       
    PhatSlider *slider;
    GtkRange   *range;
    
    double      fract;

    slider = PHAT_SLIDER(widget);
    range  = GTK_RANGE(widget);

    fract = (range->adjustment->upper - range->adjustment->value) / (range->adjustment->upper - range->adjustment->lower);
    return (int) floor (slider->view.height * (1.0 - fract));
}
