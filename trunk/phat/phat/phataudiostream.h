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

#ifndef __PHAT_AUDIOSTREAM_H__
#define __PHAT_AUDIOSTREAM_H__

#include <glib-object.h>
#include <samplerate.h>

G_BEGIN_DECLS

#define PHAT_AUDIOSTREAM(obj)          GTK_CHECK_CAST(obj, phat_audiostream_get_type(), PhatAudiostream)
#define PHAT_AUDIOSTREAM_CLASS(klass)  GTK_CHECK_CLASS_CAST(klass, phat_audiostream_get_type(), PhatAudiostreamClass)
#define PHAT_IS_AUDIOSTREAM(obj)       GTK_CHECK_TYPE(obj, phat_audiostream_get_type())
#define PHAT_TYPE_AUDIOSTREAM          (phat_audiostream_get_type ( ))


typedef struct _PhatAudiostream        PhatAudiostream;
typedef struct _PhatAudiostreamClass   PhatAudiostreamClass;

struct _PhatAudiostream {
    GObject object;


    volatile gdouble pos_est;
    volatile gdouble speed;
    volatile gdouble tmp_speed;
    //protected
    volatile    gint playpos;
    float *data;
    gint len;
    gint num_channels;

    SRC_STATE *src_state;
    SRC_DATA src_data;
    float *src_buffer;

};

struct _PhatAudiostreamClass
{
    GObjectClass parent_class;
};

GType phat_audiostream_get_type ( );

GObject* phat_audiostream_new ( char *filename );
void phat_audiostream_set_speed( PhatAudiostream *stream, gdouble speed );
//void phat_audiostream_process( PhatAudiostream *stream, jack_nframes_t nframes );
int  phat_audiostream_get_num_channels( PhatAudiostream *stream );
void phat_audiostream_render( PhatAudiostream *stream, gint nframes, float **buffers );

// XXX:
//
// need to remove the jack dependency again.
// Also add libsrc stuff.
//
// however retaining interleaved channels.
//


G_END_DECLS

#endif
