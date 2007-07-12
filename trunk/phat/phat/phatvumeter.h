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
#ifndef __PHAT_VU_METER_H__
#define __PHAT_VU_METER_H__

#include <gtk/gtkwidget.h>

G_BEGIN_DECLS


#define PHAT_TYPE_VU_METER            (phat_vu_meter_get_type ())
#define PHAT_VU_METER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), PHAT_TYPE_VU_METER, PhatVUMeter))
#define PHAT_VU_METER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PHAT_TYPE_VU_METER, PhatVUMeterClass))
#define PHAT_IS_VU_METER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PHAT_TYPE_VU_METER))
#define PHAT_IS_VU_METER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PHAT_TYPE_VU_METER))
#define PHAT_VU_METER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), PHAT_TYPE_VU_METER, PhatVUMeterClass))


typedef struct _PhatVUMeter        PhatVUMeter;
typedef struct _PhatVUMeterClass   PhatVUMeterClass;

struct _PhatVUMeter {
  GtkWidget widget;
  GdkPixbuf *pixbuf;
  float level;
};

struct _PhatVUMeterClass
{
  GtkWidgetClass parent_class;
};


GType      phat_vu_meter_get_type	  (void) G_GNUC_CONST;

GtkWidget* phat_vu_meter_new		  (void);

void       phat_vu_meter_set_level	  (PhatVUMeter  *ppm,
					   float         level);

G_END_DECLS

#endif /* __PHAT_VU_METER_H__ */
