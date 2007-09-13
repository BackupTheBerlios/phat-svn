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

#ifndef __PHAT_PLAYALINE_H__
#define __PHAT_PLAYALINE_H__

#include <gdk/gdk.h>
#include <gtk/gtkdrawingarea.h>
#include <cairo.h>
#include <phataudiostream.h>

G_BEGIN_DECLS

#define PHAT_PLAYALINE(obj)          GTK_CHECK_CAST(obj, phat_playaline_get_type(), PhatPlayaline)
#define PHAT_PLAYALINE_CLASS(klass)  GTK_CHECK_CLASS_CAST(klass, phat_playaline_get_type(), PhatPlayalineClass)
#define PHAT_IS_PLAYALINE(obj)       GTK_CHECK_TYPE(obj, phat_playaline_get_type())
#define PHAT_TYPE_PLAYALINE          (phat_playaline_get_type ( ))


typedef struct _PhatPlayaline        PhatPlayaline;
typedef struct _PhatPlayalineClass   PhatPlayalineClass;


struct _PhatPlayaline {
    GtkDrawingArea drawingarea;

    cairo_t   *cx;
    PhatAudiostream *stream;

    GtkDirectionType direction;

    GdkColor col1, col2, col3;
    GdkColor dcol1, dcol2, dcol3;
};

struct _PhatPlayalineClass
{
    GtkDrawingAreaClass parent_class;
};

GType phat_playaline_get_type ( );

GtkWidget* phat_playaline_new ( GtkDirectionType dir );
void phat_playaline_update( PhatPlayaline *playaline );
void phat_playaline_set_audio_stream( PhatPlayaline *playaline, PhatAudiostream *audio_stream );


G_END_DECLS

#endif
