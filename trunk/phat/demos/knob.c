#include <gtk/gtk.h>
#include <phat/phat.h>

enum
{
    SPACING = 0,
};

void motion_cb(PhatKnob* knob)
{
    printf("knob value %f \n", phat_knob_get_value(knob));
}  

int main (int argc, char* argv[])
{
    GtkWidget* window;
    GtkWidget* knob;
    GtkWidget* knob2;
    GtkWidget* vbox;
    gtk_init (&argc, &argv);

    /* main window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Knob Demo");
    gtk_container_set_border_width (GTK_CONTAINER (window), SPACING);
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);
    g_signal_connect (G_OBJECT (window), "delete-event",
                      G_CALLBACK (gtk_main_quit), NULL);

    vbox = gtk_vbox_new (FALSE, SPACING);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);
     
    /*  knob */
    knob = phat_knob_new_with_range (-90, -90, 0, 0.1);
    gtk_widget_set_size_request(knob,25,25);
    phat_knob_set_log((PhatKnob*) knob, 1);
    gtk_box_pack_start (GTK_BOX (vbox), knob, TRUE, FALSE, 0);
    gtk_widget_show (knob);
    g_signal_connect (G_OBJECT (knob), "value-changed",
                      G_CALLBACK (motion_cb), NULL);

    /*  knob */
    knob2 = phat_knob_new_with_range (-90, -90, 0, 0.1);
    //gtk_widget_set_size_request(knob2,45,45);
    phat_knob_set_log((PhatKnob*) knob2, 1);
    gtk_box_pack_start (GTK_BOX (vbox), knob2, TRUE, FALSE, 0);
    gtk_widget_show (knob2);
    g_signal_connect (G_OBJECT (knob2), "value-changed",
                      G_CALLBACK (motion_cb), NULL);

    gtk_widget_show (window);

    /* look if it breaks */
    gtk_widget_set_size_request(knob,20,20);

    gtk_main ( );

    return 0;
}
