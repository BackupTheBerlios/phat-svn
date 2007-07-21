/* GTK - The GIMP Toolkit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#ifndef __PHAT_RANGE_H__
#define __PHAT_RANGE_H__


#include <gdk/gdk.h>
#include <gtk/gtkadjustment.h>
#include <gtk/gtkwidget.h>


G_BEGIN_DECLS


#define PHAT_TYPE_RANGE            (phat_range_get_type ())
#define PHAT_RANGE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RANGE, PhatRange))
#define PHAT_RANGE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RANGE, PhatRangeClass))
#define PHAT_IS_RANGE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RANGE))
#define PHAT_IS_RANGE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RANGE))
#define PHAT_RANGE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RANGE, PhatRangeClass))

/* These two are private/opaque types, ignore */
typedef struct _PhatRangeLayout    PhatRangeLayout;
typedef struct _PhatRangeStepTimer PhatRangeStepTimer;

typedef struct _PhatRange        PhatRange;
typedef struct _PhatRangeClass   PhatRangeClass;

struct _PhatRange
{
  GtkWidget widget;

  GtkAdjustment *adjustment;
  GtkUpdateType update_policy;
  guint inverted : 1;

  /*< protected >*/
  
  guint flippable : 1;
  
  /* Steppers are: < > ---- < >
   *               a b      c d
   */
   
  guint has_stepper_a : 1;
  guint has_stepper_b : 1;
  guint has_stepper_c : 1;
  guint has_stepper_d : 1;

  guint need_recalc : 1;

  guint slider_size_fixed : 1;
  
  gint min_slider_size;

  GtkOrientation orientation;

  /* Area of entire stepper + trough assembly in widget->window coords */
  GdkRectangle range_rect;
  /* Slider range along the long dimension, in widget->window coords */
  gint slider_start, slider_end;

  /* Round off value to this many digits, -1 for no rounding */
  gint round_digits;
  
  /*< private >*/
  guint trough_click_forward : 1;  /* trough click was on the forward side of slider */
  guint update_pending : 1;        /* need to emit value_changed */
  PhatRangeLayout *layout;
  PhatRangeStepTimer *timer;
  gint slide_initial_slider_position;
  gint slide_initial_coordinate;
  guint update_timeout_id;
  GdkWindow *event_window;
};

struct _PhatRangeClass
{
  GtkWidgetClass parent_class;

  /* what detail to pass to GTK drawing functions */
  gchar *slider_detail;
  gchar *stepper_detail;

  void (* value_changed)    (PhatRange     *range);
  void (* adjust_bounds)    (PhatRange     *range,
                             gdouble	   new_value);
  
  /* action signals for keybindings */
  void (* move_slider)      (PhatRange     *range,
                             GtkScrollType scroll);

  /* Virtual functions */
  void (* get_range_border) (PhatRange     *range,
                             GtkBorder    *border_);

  gboolean (* change_value) (PhatRange     *range,
                             GtkScrollType scroll,
                             gdouble       new_value);

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
};


GType              phat_range_get_type                      (void) G_GNUC_CONST;

void               phat_range_set_update_policy             (PhatRange      *range,
                                                            GtkUpdateType  policy);
GtkUpdateType      phat_range_get_update_policy             (PhatRange      *range);

void               phat_range_set_adjustment                (PhatRange      *range,
                                                            GtkAdjustment *adjustment);
GtkAdjustment*     phat_range_get_adjustment                (PhatRange      *range);

void               phat_range_set_inverted                  (PhatRange      *range,
                                                            gboolean       setting);
gboolean           phat_range_get_inverted                  (PhatRange      *range);

void               phat_range_set_lower_stepper_sensitivity (PhatRange      *range,
                                                            GtkSensitivityType sensitivity);
GtkSensitivityType phat_range_get_lower_stepper_sensitivity (PhatRange      *range);
void               phat_range_set_upper_stepper_sensitivity (PhatRange      *range,
                                                            GtkSensitivityType sensitivity);
GtkSensitivityType phat_range_get_upper_stepper_sensitivity (PhatRange      *range);

void               phat_range_set_increments                (PhatRange      *range,
                                                            gdouble        step,
                                                            gdouble        page);
void               phat_range_set_range                     (PhatRange      *range,
                                                            gdouble        min,
                                                            gdouble        max);
void               phat_range_set_value                     (PhatRange      *range,
                                                            gdouble        value);
gdouble            phat_range_get_value                     (PhatRange      *range);

gdouble	          _phat_range_get_wheel_delta               (PhatRange      *range,
                                                            GdkScrollDirection direction);


G_END_DECLS


#endif /* __PHAT_RANGE_H__ */
