#include <gtk/gtk.h>
#include <phat/phat.h>

enum
{
     SPACING = 5,
};

void motion_cb(GtkAdjustment* ajd)
{
    printf("knob value %f \n", ajd->value);
}  

int main (int argc, char* argv[])
{
     GtkWidget* window;
     GtkWidget* knob;
     GtkWidget* vbox;
     PhatKnob*  knob_cast;
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
     knob = phat_knob_new_with_range (2.0, 0.0, 20, 0.1);
     knob_cast = (PhatKnob*) knob;
     gtk_box_pack_start (GTK_BOX (vbox), knob, TRUE, FALSE, 0);
     gtk_widget_show (knob);
     g_signal_connect (G_OBJECT (knob_cast->adjustment), "value-changed",
		       G_CALLBACK (motion_cb), NULL);

     gtk_widget_show (window);
     gtk_main ( );
     return 0;
}
