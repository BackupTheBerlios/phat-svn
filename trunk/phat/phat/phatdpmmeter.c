/* 
 * Digital Peak Meter for Phat. Copyright (C) 2007 Damon Chaplin.
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

#include "phatdpmmeter.h"

#define PIXMAPDIRIFY(filename) \
		(SITE_PKGDATA_DIR G_DIR_SEPARATOR_S "pixmaps" G_DIR_SEPARATOR_S filename)

G_DEFINE_TYPE (PhatDPMMeter, phat_dpm_meter, GTK_TYPE_WIDGET)


static void
phat_dpm_meter_init (PhatDPMMeter *dpm)
{
  GTK_WIDGET_SET_FLAGS (dpm, GTK_NO_WINDOW);

  dpm->pixbuf = gdk_pixbuf_new_from_file (PIXMAPDIRIFY("phatdpmmeter.png"), NULL);
  dpm->level = 0.0;
  dpm->peak_level = 0.0;
}


GtkWidget*
phat_dpm_meter_new (void)
{
  return GTK_WIDGET (g_object_new (PHAT_TYPE_DPM_METER, NULL));
}


static void
phat_dpm_meter_finalize (GObject *object)
{
  PhatDPMMeter *dpm = PHAT_DPM_METER (object);

  if (dpm->pixbuf)
    {
      g_object_unref (dpm->pixbuf);
      dpm->pixbuf = NULL;
    }

  G_OBJECT_CLASS (phat_dpm_meter_parent_class)->finalize (object);
}


static void     
phat_dpm_meter_size_request (GtkWidget      *widget,
			     GtkRequisition *requisition)
{
  PhatDPMMeter *dpm = PHAT_DPM_METER (widget);

  requisition->width = requisition->height = 0;

  if (dpm->pixbuf)
    {
      requisition->width = gdk_pixbuf_get_width (dpm->pixbuf);
      requisition->height = gdk_pixbuf_get_height (dpm->pixbuf);
    }
}


static gboolean
phat_dpm_meter_expose_event (GtkWidget      *widget,
			     GdkEventExpose *event)
{
  PhatDPMMeter *dpm = PHAT_DPM_METER (widget);
  double x, y, height;
  cairo_t *cr;

  cr = gdk_cairo_create (widget->window);

  /* Paint the background image. */
  if (dpm->pixbuf)
    gdk_draw_pixbuf (widget->window, NULL, dpm->pixbuf, 0, 0,
		     widget->allocation.x, widget->allocation.y, -1, -1,
		     GDK_RGB_DITHER_NORMAL, 0, 0);

  /* Paint the main level rectangle. */
  height = dpm->level * 200;
  x = widget->allocation.x + 7;
  y = widget->allocation.y + 5 + (200 - height);

  cairo_rectangle (cr, x, y, 9, height);
  cairo_set_source_rgb (cr, 0.94, 0.0, 0.08);
  cairo_fill (cr);

  /* Paint the peak level indicator line. */
  height = dpm->peak_level * 200;
  y = widget->allocation.y + 5 + (200 - height);

  cairo_rectangle (cr, x, y, 9, 1);
  cairo_set_source_rgb (cr, 0.86, 0.86, 0.08);
  cairo_fill (cr);

  cairo_destroy (cr);

  return FALSE;
}


void
phat_dpm_meter_set_level       (PhatDPMMeter	*dpm,
				float            level)
{
  dpm->level = level;
  /* FIXME: Only redraw when visible on screen. */
  gtk_widget_queue_draw (GTK_WIDGET (dpm));
}


void
phat_dpm_meter_set_peak_level  (PhatDPMMeter	*dpm,
				float            peak_level)
{
  dpm->peak_level = peak_level;
  gtk_widget_queue_draw (GTK_WIDGET (dpm));
}


static void
phat_dpm_meter_class_init (PhatDPMMeterClass *klass)
{
  GObjectClass *gobject_class = (GObjectClass*) klass;
  GtkWidgetClass *widget_class = (GtkWidgetClass*) klass;

  gobject_class->finalize	     = phat_dpm_meter_finalize;

  widget_class->size_request         = phat_dpm_meter_size_request;
  widget_class->expose_event         = phat_dpm_meter_expose_event;
}


