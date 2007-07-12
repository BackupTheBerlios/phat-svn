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
    GtkWidget* slider;
    GtkWidget* vbox;
    gtk_init (&argc, &argv);
    GtkAdjustment* adj;

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
    slider = phat_slider_new (adj);
    //gtk_widget_set_size_request(slider,25,25);
    gtk_box_pack_start (GTK_BOX (vbox), slider, TRUE, FALSE, 0);
    gtk_widget_show (slider);
    g_signal_connect (G_OBJECT (slider), "value-changed",
                      G_CALLBACK (motion_cb), NULL);

    gtk_widget_show (window);

    /* look if it breaks */
    //gtk_widget_set_size_request(slider,20,20);

    gtk_main ( );

    return 0;
}
