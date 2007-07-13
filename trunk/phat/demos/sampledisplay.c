#include <gtk/gtk.h>
#include <phat/phat.h>

enum
{
    SPACING = 0,
};

void motion_cb(PhatKnob* slider)
{
    //printf("slider value %f \n", phat_slider_get_value(slider));
}  

int main (int argc, char* argv[])
{
    GtkWidget* window;
    GtkWidget* sdisp;
    GtkWidget* vbox;
    gtk_init (&argc, &argv);
    GtkAdjustment* adj;

    gint16 sample[200];

    int i;
    for( i=0; i<200; i++ ) {
	sample[i] = G_MAXINT16 * ((i%50)-25) / 50;
    }
    
    /* main window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Slider Demo");
    gtk_container_set_border_width (GTK_CONTAINER (window), SPACING);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    g_signal_connect (G_OBJECT (window), "delete-event",
                      G_CALLBACK (gtk_main_quit), NULL);

    vbox = gtk_vbox_new (FALSE, SPACING);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);
     
    /*  slider */
    adj = (GtkAdjustment*) gtk_adjustment_new (1, 0, 2, .01, .1, 0);
    sdisp = sample_display_new( TRUE );
    sample_display_set_data_16( SAMPLE_DISPLAY(sdisp), sample, 200, FALSE );
    //gtk_widget_set_size_request(slider,25,25);
    gtk_box_pack_start (GTK_BOX (vbox), sdisp, TRUE, TRUE, 0);
    gtk_widget_show (sdisp);

    gtk_widget_show (window);

    /* look if it breaks */
    //gtk_widget_set_size_request(slider,20,20);

    gtk_main ( );

    return 0;
}
