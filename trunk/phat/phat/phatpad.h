#ifndef __PHAT_PAD_H__
#define __PHAT_PAD_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PHAT_TYPE_PAD            (phat_pad_get_type ( ))
#define PHAT_PAD(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), PHAT_TYPE_PAD, PhatPad))
#define PHAT_PAD_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PHAT_TYPE_PAD, PhatPadClass))
#define PHAT_IS_PAD(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PHAT_TYPE_PAD))
#define PHAT_IS_PAD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PHAT_TYPE_PAD))

typedef struct _PhatPadClass PhatPadClass;
typedef struct _PhatPad      PhatPad;

struct _PhatPad
{
    GtkDrawingArea parent; 
    GdkPixmap* pixmap;
    GtkAdjustment* pressure;
    GtkAdjustment* xtilt;
    GtkAdjustment* ytilt;
    GtkAdjustment* x;
    GtkAdjustment* y;
};

struct _PhatPadClass
{
    GtkDrawingAreaClass parent_class;

    void (*value_changed) (PhatPad* pad);
};

GType phat_pad_get_type ( );


GtkWidget* phat_pad_new ( );
gdouble phat_pad_get_ytilt (PhatPad* pad);
gdouble phat_pad_get_xtilt (PhatPad* pad);
gdouble phat_pad_get_pressure (PhatPad* pad);
gdouble phat_pad_get_y (PhatPad* pad);
gdouble phat_pad_get_x (PhatPad* pad);


G_END_DECLS

#endif /* __PHAT_PAD_H__ */
