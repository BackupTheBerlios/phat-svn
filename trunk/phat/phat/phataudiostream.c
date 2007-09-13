/* 
 *
 * Most of this code comes from gAlan 0.2.0, copyright (C) 1999
 * Tony Garnock-Jones, with modifications by Sean Bolton,
 * copyright (c) 2004.  (gtkdial.c rolls over in its grave.)
 *
 * Phatised by Loki Davison.
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

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "phataudiostream.h"

#include <sndfile.h>

/* properties */
enum
{
    PROP_0, /* oops, no props any more */
};

static void phat_audiostream_class_init         (PhatAudiostreamClass *klass);
static void phat_audiostream_init               (PhatAudiostream *audiostream);
//static void phat_audiostream_destroy            (GObject *object);

static void phat_audiostream_set_property      (GObject *object, 
                                         guint prop_id, 
                                         const GValue *value, 
                                         GParamSpec   *pspec);
static void phat_audiostream_get_property      (GObject *object, 
                                         guint prop_id, 
                                         GValue *value, 
                                         GParamSpec *pspec);


/* Local data */

G_DEFINE_TYPE (PhatAudiostream, phat_audiostream, G_TYPE_OBJECT);

static void phat_audiostream_class_init (PhatAudiostreamClass *klass) {
    GObjectClass     *g_object_class;

    g_object_class = G_OBJECT_CLASS(klass);

    g_object_class->set_property = phat_audiostream_set_property;
    g_object_class->get_property = phat_audiostream_get_property;

    //FIXME: Destructor
}

static void phat_audiostream_init (PhatAudiostream *audiostream) {
    audiostream->pos_est = 0.0;
    audiostream->speed = 1.0;
    audiostream->tmp_speed = 0.0;

    audiostream->playpos = 0;
    audiostream->data = NULL;
    audiostream->len = 0;
    audiostream->num_channels = 2;

    audiostream->src_data.data_in = NULL;
    audiostream->src_data.data_out = NULL;
    audiostream->src_data.input_frames = 0;
    audiostream->src_data.output_frames = 0;
    audiostream->src_data.input_frames_used = 0;
    audiostream->src_data.output_frames_gen = 0;
    audiostream->src_data.end_of_input = 0;
    audiostream->src_data.src_ratio = 1.0;

    //audiostream->src_state = src_new( SRC_SINC_BEST_QUALITY, audiostream->num_channels, NULL );
    audiostream->src_state = src_new( SRC_LINEAR, audiostream->num_channels, NULL );
}


GObject *phat_audiostream_new( char *filename ) {

    GObject *retval = g_object_new (PHAT_TYPE_AUDIOSTREAM, NULL);

    PhatAudiostream *stream = (PhatAudiostream *)  retval;

    // load file;
    SF_INFO info;
    SNDFILE *file = sf_open( filename, SFM_READ, &info );

    stream->data = malloc( sizeof(float) * info.frames * info.channels );
    if( stream->data == NULL ) {
	printf( "No Mem for audio file\n" );
	exit(20);
    }

    sf_readf_float( file, stream->data, info.frames );
    sf_close( file );

    stream->len = info.frames;
    stream->num_channels = info.channels;

    stream->src_buffer = malloc( sizeof(float) * 4096 * info.channels );
    if( stream->src_buffer == NULL ) {
	printf( "No Mem for Src Buffer\n" );
	exit(20);
    }


    return retval;
}

void phat_audiostream_set_speed( PhatAudiostream *stream, gdouble speed ) {
    stream->speed = speed;
    // XXX: emit speed changed;
}

gint phat_audiostream_get_num_channels( PhatAudiostream *stream ) {
    return stream->num_channels;
}

#if 0
void phat_audiostream_process( PhatAudiostream *stream, jack_nframes_t nframes ) {
    float *dat1 = jack_port_get_buffer( stream->out_left, nframes );
    float *dat2 = jack_port_get_buffer( stream->out_right, nframes );

    jack_nframes_t i;
    for( i=0; i<nframes; i++ ) {
	dat1[i] = stream->data[ (stream->playpos+i) * 2 ];
	dat2[i] = stream->data[ (stream->playpos+i) * 2 + 1 ];
    }
    stream->playpos += nframes;

}
#endif 

void phat_audiostream_render( PhatAudiostream *stream, gint nframes, float **buffers ) {

    gint num_channels = phat_audiostream_get_num_channels( stream );

    SRC_DATA *src = & (stream->src_data);

    src->data_out = stream->src_buffer;
    src->data_in = stream->data + (stream->playpos * num_channels);

    src->input_frames = stream->len - stream->playpos;
    src->output_frames = nframes;
    src->end_of_input = 0; // FIXME: real check;
    src->src_ratio = stream->speed + stream->tmp_speed;

    src_process( stream->src_state, src );

    gint i,c;
    for( i=0; i<nframes; i++ ) {
	for( c=0; c<num_channels; c++ ) {
	    buffers[c][i] = stream->src_buffer[ i * num_channels + c ];
	}
    }

    if( src->input_frames_used != 0 ) {
	stream->playpos += src->input_frames_used;
	stream->pos_est = (gdouble) stream->playpos;
    } else {
	stream->pos_est += ( ((gdouble)nframes) / (stream->speed + stream->tmp_speed) );
    }
}


static void
phat_audiostream_set_property (GObject      *object, 
                        guint         prop_id, 
                        const GValue *value, 
                        GParamSpec   *pspec)
{
    //PhatAudiostream *audiostream = PHAT_AUDIOSTREAM (object);

    switch (prop_id) 
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}

static void
phat_audiostream_get_property (GObject    *object, 
                        guint       prop_id, 
                        GValue     *value, 
                        GParamSpec *pspec)
{
    //PhatAudiostream *audiostream = PHAT_AUDIOSTREAM (object);
    
    switch (prop_id) 
    {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
        break;
    }
}
