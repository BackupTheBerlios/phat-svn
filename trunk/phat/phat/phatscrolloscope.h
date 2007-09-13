/* 
 *
 * Most of this code comes from gAlan 0.2.0, copyright (C) 1999
 * Tony Garnock-Jones, with modifications by Sean Bolton,
 * copyright (c) 2004.
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

#ifndef __PHAT_SCROLLOSCOPE_H__
#define __PHAT_SCROLLOSCOPE_H__

#include <gdk/gdk.h>
#include <gtk/gtkdrawingarea.h>
#include <cairo.h>
#include <phataudiostream.h>

G_BEGIN_DECLS

#define PHAT_SCROLLOSCOPE(obj)          GTK_CHECK_CAST(obj, phat_scrolloscope_get_type(), PhatScrolloscope)
#define PHAT_SCROLLOSCOPE_CLASS(klass)  GTK_CHECK_CLASS_CAST(klass, phat_scrolloscope_get_type(), PhatScrolloscopeClass)
#define PHAT_IS_SCROLLOSCOPE(obj)       GTK_CHECK_TYPE(obj, phat_scrolloscope_get_type())
#define PHAT_TYPE_SCROLLOSCOPE          (phat_scrolloscope_get_type ( ))


typedef struct _PhatScrolloscope        PhatScrolloscope;
typedef struct _PhatScrolloscopeClass   PhatScrolloscopeClass;


struct _PhatScrolloscope {
    GtkDrawingArea drawingarea;

    cairo_t   *cx;

    //gint last_pos;
    gint current_pixel_pos;
    gint last_pixel_pos;
    gdouble zoomx, zoomy;
    PhatAudiostream *stream;
    gdouble last_speed;
    gboolean dirty;
    gboolean scroll;
    gint smooth;
    gfloat diff_threshold;
    GtkDirectionType direction;
    gdouble saved_x, saved_y;
    gint state;

    GdkColor col1, col2, col3;
    GdkColor dcol1, dcol2, dcol3;
};

struct _PhatScrolloscopeClass
{
    GtkDrawingAreaClass parent_class;
};

GType phat_scrolloscope_get_type ( );

GtkWidget* phat_scrolloscope_new ( GtkDirectionType dir );
void phat_scrolloscope_update( PhatScrolloscope *scrollo );
void phat_scrolloscope_set_audio_stream( PhatScrolloscope *scrollo, PhatAudiostream *audio_stream );


G_END_DECLS

#endif
