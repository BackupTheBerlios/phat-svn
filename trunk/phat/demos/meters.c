#include <gtk/gtk.h>
#include "phatdpmmeter.h"
#include "phatppmmeter.h"
#include "phatvumeter.h"


GtkWidget *dpm, *ppm, *vu;

float dpm_level_step = 0.07;
const float dpm_max_level = 1.0;
const float dpm_min_level = 0.0;

float ppm_level_step = 0.07;
const float ppm_max_level = 1.0;
const float ppm_min_level = 0.0;

float vu_level_step = 0.07;
const float vu_max_level = 1.0;
const float vu_min_level = 0.0;


static gboolean
timeout_cb (gpointer unused)
{
  static float dpm_level = 0.0;
  static float ppm_level = 0.0;
  static float vu_level = 0.0;

  dpm_level += dpm_level_step;
  if (dpm_level > dpm_max_level || dpm_level < dpm_min_level)
    dpm_level_step = -dpm_level_step;
  dpm_level = CLAMP (dpm_level, dpm_min_level, dpm_max_level);
  phat_dpm_meter_set_level (PHAT_DPM_METER (dpm), dpm_level);

  ppm_level += ppm_level_step;
  if (ppm_level > ppm_max_level || ppm_level < ppm_min_level)
    ppm_level_step = -ppm_level_step;
  ppm_level = CLAMP (ppm_level, ppm_min_level, ppm_max_level);
  phat_ppm_meter_set_level (PHAT_PPM_METER (ppm), ppm_level);

  vu_level += vu_level_step;
  if (vu_level > vu_max_level || vu_level < vu_min_level)
    vu_level_step = -vu_level_step;
  vu_level = CLAMP (vu_level, vu_min_level, vu_max_level);
  phat_vu_meter_set_level (PHAT_VU_METER (vu), vu_level);

  return TRUE;
}


int
main (int argc, char *argv[])
{
  GtkWidget *window, *hbox;

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW (window), 500, 250);
  gtk_widget_show (window);
  g_signal_connect (window, "delete_event", (GtkSignalFunc) gtk_main_quit,
		    NULL);

  hbox = gtk_hbox_new (FALSE, 4);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 4);
  gtk_widget_show (hbox);
  gtk_container_add (GTK_CONTAINER (window), hbox);

  dpm = phat_dpm_meter_new ();
  gtk_widget_show (dpm);
  gtk_box_pack_start (GTK_BOX (hbox), dpm, FALSE, FALSE, 12);
  phat_dpm_meter_set_peak_level (PHAT_DPM_METER (dpm), 0.8);

  ppm = phat_ppm_meter_new ();
  gtk_widget_show (ppm);
  gtk_box_pack_start (GTK_BOX (hbox), ppm, FALSE, FALSE, 12);

  vu = phat_vu_meter_new ();
  gtk_widget_show (vu);
  gtk_box_pack_start (GTK_BOX (hbox), vu, FALSE, FALSE, 12);

  g_timeout_add (100, timeout_cb, NULL);

  gtk_main ();

  return 0;
}
