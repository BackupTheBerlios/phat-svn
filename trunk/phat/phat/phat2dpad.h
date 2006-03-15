#ifndef __PHAT_2D_PAD_H__
#define __PHAT_2D_PAD_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define PHAT_TYPE_2D_PAD            (phat_2d_pad_get_type ( ))
#define PHAT_2D_PAD(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), PHAT_TYPE_2D_PAD, Phat2dPad))
#define PHAT_2D_PAD_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), PHAT_TYPE_2D_PAD, Phat2dPadClass))
#define PHAT_IS_2D_PAD(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), PHAT_TYPE_2D_PAD))
#define PHAT_IS_2D_PAD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), PHAT_TYPE_2D_PAD))

typedef struct _Phat2dPadClass Phat2dPadClass;
typedef struct _Phat2dPad      Phat2dPad;

struct _Phat2dPad
{
    GtkDrawingArea parent; 
    GdkPixmap* pixmap;
};

struct _Phat2dPadClass
{
    GtkDrawingAreaClass parent_class;

    //void (*value_changed) (Phat2dPad* slider);
    //void (*changed)       (Phat2dPad* slider);
};

GType phat_2d_pad_get_type ( );


GtkWidget* phat_2d_pad_new ( );

G_END_DECLS

#endif /* __PHAT_2D_PAD_H__ */
