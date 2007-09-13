

#include <gtk/gtk.h>

#include <phat/phataudiostream.h>

#include <phat/phatscrolloscope.h>
#include <phat/phatplayaline.h>
#include <phat/phatknob.h>

#include <sndfile.h>
#include <jack/jack.h>
#include <stdlib.h>

enum SPACI {
    SPACING = 0,
};


float *audio;
int audio_frames;

jack_port_t *p1, *p2, *p3, *p4;
int playhead = 0;

GObject *s1, *s2;


// process()
//

int jack_process( jack_nframes_t nframes, PhatAudiostream *stream ) {

    float **buffers = alloca( sizeof( float *) * 2 );
    buffers[0] = jack_port_get_buffer( p1, nframes );
    buffers[1] = jack_port_get_buffer( p2, nframes );
    phat_audiostream_render( PHAT_AUDIOSTREAM(s1), nframes, buffers );
    buffers[0] = jack_port_get_buffer( p3, nframes );
    buffers[1] = jack_port_get_buffer( p4, nframes );
    phat_audiostream_render( PHAT_AUDIOSTREAM(s2), nframes, buffers );
    return 0;
}

// callbacks
//

gboolean scroll_func(PhatScrolloscope* scrollo) {
    phat_scrolloscope_update( scrollo );
    return TRUE;
}  

void speedknob_cb(PhatKnob* knob, PhatScrolloscope *scrollo ) {
    gdouble val = phat_knob_get_value(knob);
    scrollo->stream->speed = val;
}  

void zoomxknob_cb(PhatKnob* knob, PhatScrolloscope *scrollo ) {
    gdouble val = phat_knob_get_value(knob);

    scrollo->zoomx = val;
    scrollo->dirty = TRUE;
}  

void zoomyknob_cb(PhatKnob* knob, PhatScrolloscope *scrollo ) {
    gdouble val = phat_knob_get_value(knob);

    scrollo->zoomy = val;
    scrollo->dirty = TRUE;
}  

// And the main() 
//

int main (int argc, char* argv[]) {
    GtkWidget *window;
    GtkWidget *scrollo, *scrollo2;
    GtkWidget *playaline;
    GtkWidget *speedknob, *speedknob2, *zoomxknob, *zoomyknob;
    GtkWidget *vbox1, *vbox2, *hbox;

    gtk_init (&argc, &argv);

    // jack_client
    jack_client_t *client = jack_client_open( "phatplaya", 0, NULL );
    p1 = jack_port_register( client, "out1", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0 );
    p2 = jack_port_register( client, "out2", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0 );
    p3 = jack_port_register( client, "out3", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0 );
    p4 = jack_port_register( client, "out4", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0 );
    
    // audio stream
    s1 = phat_audiostream_new( argv[1] );
    phat_audiostream_set_speed( PHAT_AUDIOSTREAM(s1), 1.0 );

    s2 = phat_audiostream_new( argv[1] );
    phat_audiostream_set_speed( PHAT_AUDIOSTREAM(s2), 1.0 );

    // run jack
    jack_set_process_callback( client, (JackProcessCallback) jack_process, s1 );
    jack_activate( client );

    /* main window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Scrollo Demo (phatplaya)");
    gtk_container_set_border_width (GTK_CONTAINER (window), SPACING);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    g_signal_connect (G_OBJECT (window), "delete-event",
                      G_CALLBACK (gtk_main_quit), NULL);

    // boxen
    hbox = gtk_hbox_new (FALSE, SPACING);
    gtk_container_add (GTK_CONTAINER (window), hbox);
    gtk_widget_show (hbox);

    vbox1 = gtk_vbox_new (FALSE, SPACING);
    gtk_box_pack_start (GTK_BOX (hbox), vbox1, FALSE, TRUE, 0);
    gtk_widget_show (vbox1);

    vbox2 = gtk_vbox_new (FALSE, SPACING);
    gtk_box_pack_end (GTK_BOX (hbox), vbox2, TRUE, TRUE, 0);
    gtk_widget_show (vbox2);

    // knobs
    speedknob = phat_knob_new_with_range( 1.0, 0.9, 1.1, 0.001 );
    gtk_box_pack_start (GTK_BOX (vbox1), speedknob, FALSE, TRUE, 0);
    gtk_widget_show( speedknob );

    speedknob2 = phat_knob_new_with_range( 1.0, 0.9, 1.1, 0.001 );
    gtk_box_pack_start (GTK_BOX (vbox1), speedknob2, FALSE, TRUE, 0);
    gtk_widget_show( speedknob2 );

    zoomxknob = phat_knob_new_with_range( 5.0, 0.2, 20.1, 0.1 );
    gtk_box_pack_end (GTK_BOX (vbox1), zoomxknob, FALSE, TRUE, 0);
    gtk_widget_show( zoomxknob );

    zoomyknob = phat_knob_new_with_range( 1, 0.001, 40.0, 0.01 );
    gtk_box_pack_end (GTK_BOX (vbox1), zoomyknob, FALSE, TRUE, 0);
    gtk_widget_show( zoomyknob );

    // upper playaline
    playaline = phat_playaline_new( GTK_DIR_DOWN );
    gtk_box_pack_start (GTK_BOX (vbox2), playaline, FALSE, TRUE, 0);
    gtk_widget_show (playaline);

    // the scrollo
    scrollo = phat_scrolloscope_new( GTK_DIR_DOWN );
    phat_scrolloscope_set_audio_stream( PHAT_SCROLLOSCOPE(scrollo), PHAT_AUDIOSTREAM(s1) );

    // connect knobs;
    g_signal_connect (G_OBJECT (speedknob), "value-changed",
                      G_CALLBACK (speedknob_cb), scrollo );
    g_signal_connect (G_OBJECT (zoomxknob), "value-changed",
                      G_CALLBACK (zoomxknob_cb), scrollo );
    g_signal_connect (G_OBJECT (zoomyknob), "value-changed",
                      G_CALLBACK (zoomyknob_cb), scrollo );
     

    gtk_box_pack_start (GTK_BOX (vbox2), scrollo, TRUE, TRUE, 0);
    gtk_widget_show (scrollo);

    scrollo2 = phat_scrolloscope_new( GTK_DIR_UP );
    phat_scrolloscope_set_audio_stream( PHAT_SCROLLOSCOPE(scrollo2), PHAT_AUDIOSTREAM(s2) );

    // connect knobs;
    g_signal_connect (G_OBJECT (speedknob2), "value-changed",
                      G_CALLBACK (speedknob_cb), scrollo2 );
    g_signal_connect (G_OBJECT (zoomxknob), "value-changed",
                      G_CALLBACK (zoomxknob_cb), scrollo2 );
    g_signal_connect (G_OBJECT (zoomyknob), "value-changed",
                      G_CALLBACK (zoomyknob_cb), scrollo2 );
     

    gtk_box_pack_start (GTK_BOX (vbox2), scrollo2, TRUE, TRUE, 0);
    gtk_widget_show (scrollo2);
    
    playaline = phat_playaline_new( GTK_DIR_UP );
    gtk_box_pack_end (GTK_BOX (vbox2), playaline, FALSE, TRUE, 0);
    gtk_widget_show (playaline);

    gtk_widget_show (window);


    g_timeout_add( 15, (GSourceFunc) scroll_func, scrollo );
    g_timeout_add( 15, (GSourceFunc) scroll_func, scrollo2 );
    gtk_main ( );

    jack_deactivate( client );
    return 0;
}
