/* 
 * Slider for Phat. Copyright (C) 2007 Loki Davison.
 * Ported from Ardour, original version by Paul Davis, designed by Thorsten Wilms.
 *  
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

#ifndef __PHAT_SLIDER_H__
#define __PHAT_SLIDER_H__

#include <gdk/gdk.h>
#include <gtk/gtkadjustment.h>
#include <gtk/gtkwidget.h>

G_BEGIN_DECLS

#define PHAT_SLIDER(obj)          GTK_CHECK_CAST(obj, phat_slider_get_type(), PhatSlider)
#define PHAT_SLIDER_CLASS(klass)  GTK_CHECK_CLASS_CAST(klass, phat_slider_get_type(), PhatSliderClass)
#define PHAT_IS_SLIDER(obj)       GTK_CHECK_TYPE(obj, phat_slider_get_type())
#define PHAT_TYPE_SLIDER          (phat_slider_get_type ( ))


typedef struct _PhatSlider        PhatSlider;
typedef struct _PhatSliderClass   PhatSliderClass;

struct _PhatSlider {
    GtkWidget widget;
    /* The adjustment object that stores the data for this slider */
    GtkAdjustment *adjustment;

    //what does this do?
    /* update policy (GTK_UPDATE_[CONTINUOUS/DELAYED/DISCONTINUOUS]) */
    //guint policy : 2;

    gint pixheight;

    GdkRectangle view;

    GdkPixbuf *pixbuf;
    GdkWindow* grab_window;
    double grab_y;
    double grab_start;
    int last_drawn;
    gboolean dragging;
    float default_value;
    int unity_y;

};

struct _PhatSliderClass
{
    GtkWidgetClass parent_class;

    void (*value_changed) (PhatSlider* slider);
};

GType phat_slider_get_type ( );

GtkWidget* phat_slider_new (GtkAdjustment* adjustment);

GtkWidget* phat_slider_new_with_range (double value,
                                     double lower,
                                     double upper,
                                     double step);
GtkAdjustment *phat_slider_get_adjustment(PhatSlider *slider);
double phat_slider_get_value (PhatSlider* slider);
void phat_slider_set_value (PhatSlider* slider, double value);
void phat_slider_set_range (PhatSlider* slider, double lower, double upper);
void phat_slider_set_adjustment(PhatSlider *slider, GtkAdjustment *adjustment);

G_END_DECLS

#endif
