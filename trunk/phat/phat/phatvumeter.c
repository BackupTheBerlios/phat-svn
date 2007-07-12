/* 
 * Volume Unit Meter for Phat. Copyright (C) 2007 Damon Chaplin.
 * Ported from JACK Meterbridge by Steve Harris.
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
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <math.h>
#include "phatvumeter.h"

#define PIXMAPDIRIFY(filename) \
		(SITE_PKGDATA_DIR G_DIR_SEPARATOR_S "pixmaps" G_DIR_SEPARATOR_S filename)

G_DEFINE_TYPE (PhatVUMeter, phat_vu_meter, GTK_TYPE_WIDGET)


static void
phat_vu_meter_init (PhatVUMeter *vu)
{
  GTK_WIDGET_SET_FLAGS (vu, GTK_NO_WINDOW);

  vu->pixbuf = gdk_pixbuf_new_from_file (PIXMAPDIRIFY("phatvumeter.png"), NULL);
  vu->level = 0.0;
}


GtkWidget*
phat_vu_meter_new (void)
{
  return GTK_WIDGET (g_object_new (PHAT_TYPE_VU_METER, NULL));
}


static void
phat_vu_meter_finalize (GObject *object)
{
  PhatVUMeter *vu = PHAT_VU_METER (object);

  if (vu->pixbuf)
    {
      g_object_unref (vu->pixbuf);
      vu->pixbuf = NULL;
    }

  G_OBJECT_CLASS (phat_vu_meter_parent_class)->finalize (object);
}


static void     
phat_vu_meter_size_request (GtkWidget      *widget,
			     GtkRequisition *requisition)
{
  PhatVUMeter *vu = PHAT_VU_METER (widget);

  requisition->width = requisition->height = 0;

  if (vu->pixbuf)
    {
      requisition->width = gdk_pixbuf_get_width (vu->pixbuf);
      requisition->height = gdk_pixbuf_get_height (vu->pixbuf);
    }
}


static const double needle_len = 98.0f;
static const double needle_hub = 21.0f;
static const double pi_2 = 1.570796f;
static const double pi_4 = 0.785398f;

static gboolean
phat_vu_meter_expose_event (GtkWidget      *widget,
			    GdkEventExpose *event)
{
  PhatVUMeter *vu = PHAT_VU_METER (widget);
  double theta, origin_x, origin_y, sin_theta, cos_theta, x1, y1, x2, y2;
  cairo_t *cr;

  cr = gdk_cairo_create (widget->window);

  /* Paint the background image. */
  if (vu->pixbuf)
    gdk_draw_pixbuf (widget->window, NULL, vu->pixbuf, 0, 0,
		     widget->allocation.x, widget->allocation.y, -1, -1,
		     GDK_RGB_DITHER_NORMAL, 0, 0);

  /* Paint the needle. */
  theta = (vu->level * pi_2) - pi_4;
  origin_x = widget->allocation.x + 108.5;
  origin_y = widget->allocation.y + 169.5;
  sin_theta = sin (theta);
  cos_theta = cos (theta);
  x1 = origin_x + (sin_theta * needle_hub);
  y1 = origin_y - (cos_theta * needle_hub);
  x2 = origin_x + (sin_theta * needle_len);
  y2 = origin_y - (cos_theta * needle_len);

  cairo_set_line_width (cr, 1.6);
  cairo_move_to (cr, x1, y1);
  cairo_line_to (cr, x2, y2);
  cairo_set_source_rgb (cr, 0.3, 0.3, 0.3);
  cairo_stroke (cr);

  cairo_destroy (cr);

  return FALSE;
}


void
phat_vu_meter_set_level       (PhatVUMeter	*vu,
			       float             level)
{
  GtkWidget *widget = GTK_WIDGET (vu);
  double origin_x, origin_y, max_x_offset;

  vu->level = level;

  origin_x = widget->allocation.x + 108.5;
  origin_y = widget->allocation.y + 169.5;
  max_x_offset = sin (pi_4) * needle_len;

#if 0
  gtk_widget_queue_draw (GTK_WIDGET (vu));
#else
  /* Just queue a redraw of the area containing the needle. */
  gtk_widget_queue_draw_area (GTK_WIDGET (vu),
			      origin_x - max_x_offset, origin_y - needle_len,
			      max_x_offset * 2, needle_len);
#endif
}


static void
phat_vu_meter_class_init (PhatVUMeterClass *klass)
{
  GObjectClass *gobject_class = (GObjectClass*) klass;
  GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

  gobject_class->finalize	     = phat_vu_meter_finalize;

  widget_class->size_request         = phat_vu_meter_size_request;
  widget_class->expose_event         = phat_vu_meter_expose_event;
}


