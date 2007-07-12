/* 
 * Peak Program Meter for Phat. Copyright (C) 2007 Damon Chaplin.
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
#include "phatppmmeter.h"

#define PIXMAPDIRIFY(filename) \
		(SITE_PKGDATA_DIR G_DIR_SEPARATOR_S "pixmaps" G_DIR_SEPARATOR_S filename)

G_DEFINE_TYPE (PhatPPMMeter, phat_ppm_meter, GTK_TYPE_WIDGET)


static void
phat_ppm_meter_init (PhatPPMMeter *ppm)
{
  GTK_WIDGET_SET_FLAGS (ppm, GTK_NO_WINDOW);

  ppm->pixbuf = gdk_pixbuf_new_from_file (PIXMAPDIRIFY("phatppmmeter.png"), NULL);
  ppm->level = 0.0;
}


GtkWidget*
phat_ppm_meter_new (void)
{
  return GTK_WIDGET (g_object_new (PHAT_TYPE_PPM_METER, NULL));
}


static void
phat_ppm_meter_finalize (GObject *object)
{
  PhatPPMMeter *ppm = PHAT_PPM_METER (object);

  if (ppm->pixbuf)
    {
      g_object_unref (ppm->pixbuf);
      ppm->pixbuf = NULL;
    }

  G_OBJECT_CLASS (phat_ppm_meter_parent_class)->finalize (object);
}


static void     
phat_ppm_meter_size_request (GtkWidget      *widget,
			     GtkRequisition *requisition)
{
  PhatPPMMeter *ppm = PHAT_PPM_METER (widget);

  requisition->width = requisition->height = 0;

  if (ppm->pixbuf)
    {
      requisition->width = gdk_pixbuf_get_width (ppm->pixbuf);
      requisition->height = gdk_pixbuf_get_height (ppm->pixbuf);
    }
}


static gboolean
phat_ppm_meter_expose_event (GtkWidget      *widget,
			     GdkEventExpose *event)
{
  PhatPPMMeter *ppm = PHAT_PPM_METER (widget);
  const double needle_len = 82.0f;
  const double needle_hub = 16.0f;
  const double pi_2 = 1.570796f;
  const double pi_4 = 0.785398f;
  double theta, origin_x, origin_y, x1, y1, x2, y2;
  cairo_t *cr;

  cr = gdk_cairo_create (widget->window);

  /* Paint the background image. */
  if (ppm->pixbuf)
    gdk_draw_pixbuf (widget->window, NULL, ppm->pixbuf, 0, 0,
		     widget->allocation.x, widget->allocation.y, -1, -1,
		     GDK_RGB_DITHER_NORMAL, 0, 0);

  /* Paint the needle. */
  theta = (ppm->level * pi_2) - pi_4;
  origin_x = widget->allocation.x + 89.5;
  origin_y = widget->allocation.y + 138.5;
  x1 = origin_x + (sin (theta) * needle_hub);
  y1 = origin_y - (cos (theta) * needle_hub);
  x2 = origin_x + (sin (theta) * needle_len);
  y2 = origin_y - (cos (theta) * needle_len);

  cairo_set_line_width (cr, 1.6);
  cairo_move_to (cr, x1, y1);
  cairo_line_to (cr, x2, y2);
  cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
  cairo_stroke (cr);

  cairo_destroy (cr);

  return FALSE;
}


void
phat_ppm_meter_set_level       (PhatPPMMeter	*ppm,
				float            level)
{
  ppm->level = level;
  gtk_widget_queue_draw (GTK_WIDGET (ppm));
}


static void
phat_ppm_meter_class_init (PhatPPMMeterClass *klass)
{
  GObjectClass *gobject_class = (GObjectClass*) klass;
  GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

  gobject_class->finalize	     = phat_ppm_meter_finalize;

  widget_class->size_request         = phat_ppm_meter_size_request;
  widget_class->expose_event         = phat_ppm_meter_expose_event;
}


