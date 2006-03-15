#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "phatprivate.h"
#include "phat2dpad.h"

/* signals */
enum
{
    CHANGED_SIGNAL,
    VALUE_CHANGED_SIGNAL,
    LAST_SIGNAL,
};

/* hilite states */
enum
{
    LEFT_ARROW = 1,
    RIGHT_ARROW,
    LABEL,
};

/* action states */
enum
{
    STATE_NORMAL,
    STATE_PRESSED,
    STATE_SLIDE,
    STATE_ENTRY,
    STATE_SCROLL,
};

/* magic numbers */
enum
{
    SCROLL_THRESHOLD = 4,
    DIGITS = 2,
    MAXDIGITS = 20,
};


static GtkHBoxClass* parent_class;
//static int signals[LAST_SIGNAL];


static void phat_2d_pad_class_init               (Phat2dPadClass* klass);
static void phat_2d_pad_init                     (Phat2dPad* pad);
static void phat_2d_pad_destroy                  (GtkObject* object);
static void phat_2d_pad_realize                  (GtkWidget* widget);
static void phat_2d_pad_unrealize                (GtkWidget* widget);
static void phat_2d_pad_map                      (GtkWidget* widget);
static void phat_2d_pad_unmap                    (GtkWidget* widget);
static void phat_2d_pad_size_allocate            (GtkWidget* widget,
							 GtkAllocation* allocation);
static gboolean phat_2d_pad_expose               (GtkWidget* widget,
							 GdkEventExpose* event);
static gboolean phat_2d_pad_button_press         (GtkWidget* widget,
							 GdkEventButton* event);
static gboolean phat_2d_pad_motion_notify        (GtkWidget* widget,
							 GdkEventMotion* event);
static gboolean phat_2d_pad_configure_event		 (GtkWidget *widget, 
							 GdkEventConfigure *event);

GType phat_2d_pad_get_type ( )
{
    static GType type = 0;

    if (!type)
    {
	static const GTypeInfo info =
	    {
		sizeof (Phat2dPadClass),
		NULL,
		NULL,
		(GClassInitFunc) phat_2d_pad_class_init,
		NULL,
		NULL,
		sizeof (Phat2dPad),
		0,
		(GInstanceInitFunc) phat_2d_pad_init,
	    };

	type = g_type_register_static (GTK_TYPE_DRAWING_AREA,
				       "Phat2dPad",
				       &info,
				       0);
    }

    return type;
}



/**
 * phat_2d_pad_new:
 * @digits: number of decimal digits to display
 * 
 * Creates a new #Phat2dPad.
 *
 * Returns: a newly created #Phat2dPad
 * 
 */
GtkWidget* phat_2d_pad_new ()
{
    Phat2dPad* pad;

    debug ("new\n");

    pad = g_object_new (PHAT_TYPE_2D_PAD, NULL);
         
    return (GtkWidget*) pad;
}

static void phat_2d_pad_class_init (Phat2dPadClass* klass)
{
    GtkObjectClass* object_class = (GtkObjectClass*) klass;
    GtkWidgetClass* widget_class = (GtkWidgetClass*) klass;

    debug ("class init\n");
     
    parent_class = gtk_type_class (gtk_drawing_area_get_type ());

    object_class->destroy = phat_2d_pad_destroy;

    widget_class->realize = phat_2d_pad_realize;
    widget_class->unrealize = phat_2d_pad_unrealize;
    widget_class->map = phat_2d_pad_map;
    widget_class->unmap = phat_2d_pad_unmap;
    widget_class->size_allocate = phat_2d_pad_size_allocate;
    widget_class->expose_event = phat_2d_pad_expose;
    widget_class->button_press_event = phat_2d_pad_button_press;
    widget_class->motion_notify_event = phat_2d_pad_motion_notify;

    /**
     * Phat2dPad::value-changed:
     * @pad: the object on which the signal was emitted
     *
     * The "value-changed" signal is emitted when the value of the
     * pad's adjustment changes.
     *
     */
    /*
    signals[VALUE_CHANGED_SIGNAL] =
	g_signal_new ("value-changed",
		      G_TYPE_FROM_CLASS (klass),
		      G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION,
		      G_STRUCT_OFFSET (Phat2dPadClass, value_changed),
		      NULL, NULL,
		      g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0); */
     
    //klass->value_changed = NULL;
}



static void phat_2d_pad_init (Phat2dPad* pad)
{
    debug ("init\n");

    GtkWidget* widget = GTK_WIDGET (pad);
    int focus_width, focus_pad;
    
    
    GTK_WIDGET_SET_FLAGS (widget, GTK_CAN_FOCUS);
     
    /* our parent class sets this to false; we need it to be true so
     * that we are drawn without glitches when first shown
     * (mapped) */
    //gtk_widget_set_redraw_on_allocate (GTK_WIDGET (box), TRUE);
    
    pad->pixmap = NULL;
    gtk_widget_set_size_request (GTK_WIDGET (pad), 200, 200);
         

    gtk_widget_style_get (widget,
			  "focus-line-width", &focus_width,
			  "focus-padding", &focus_pad,
			  NULL);
    
    g_signal_connect (G_OBJECT (pad), "expose_event",
                    G_CALLBACK (phat_2d_pad_expose), NULL);
    g_signal_connect (G_OBJECT(pad),"configure_event",
                    G_CALLBACK (phat_2d_pad_configure_event), NULL);

    /* Event signals */

    g_signal_connect (G_OBJECT (pad), "motion_notify_event",
			G_CALLBACK (phat_2d_pad_motion_notify), NULL);
    g_signal_connect (G_OBJECT (pad), "button_press_event",
			G_CALLBACK (phat_2d_pad_button_press), NULL);

    gtk_widget_set_events (widget, GDK_EXPOSURE_MASK
			     | GDK_LEAVE_NOTIFY_MASK
			     | GDK_BUTTON_PRESS_MASK
			     | GDK_POINTER_MOTION_MASK
			     | GDK_POINTER_MOTION_HINT_MASK);

    /* The following call enables tracking and processing of extension
	 events for the drawing area */
    gtk_widget_set_extension_events (widget, GDK_EXTENSION_EVENTS_CURSOR);
    
    /*g_signal_connect (G_OBJECT (pad->entry), "activate",
		      G_CALLBACK (phat_2d_pad_entry_activate), (gpointer) pad);*/
}



static void phat_2d_pad_destroy (GtkObject* object)
{
    GtkObjectClass* klass;
    Phat2dPad* pad;
    GtkWidget* widget;
     
    debug ("destroy %p\n", object);
     
    g_return_if_fail (object != NULL);
    g_return_if_fail (PHAT_IS_2D_PAD(object));

    klass = GTK_OBJECT_CLASS (parent_class);
    pad = (Phat2dPad*) object;
    widget = GTK_WIDGET (object);

   
    if (pad->pixmap)
    {
	//gtk_widget_destroy (pad->pixmap);
	pad->pixmap = NULL;
    }
      
    if (klass->destroy)
	klass->destroy (object);
}



static void phat_2d_pad_realize (GtkWidget* widget)
{
    GtkWidgetClass* klass = GTK_WIDGET_CLASS (parent_class);
    //Phat2dPad* pad = (Phat2dPad*) widget;
        
    debug ("realize\n");
     
    g_return_if_fail (widget != NULL);
    g_return_if_fail (PHAT_IS_2D_PAD(widget));

    if (klass->realize)
	klass->realize (widget);

}



static void phat_2d_pad_unrealize (GtkWidget *widget)
{
    //Phat2dPad* pad = PHAT_2D_PAD(widget);
    GtkWidgetClass* klass = GTK_WIDGET_CLASS (parent_class);

    debug ("unrealize\n");
     
     
    if (klass->unrealize)
	klass->unrealize (widget);
}


static void phat_2d_pad_map (GtkWidget *widget)
{
    Phat2dPad* pad;

    debug ("map\n");
     
    g_return_if_fail (PHAT_IS_2D_PAD(widget));
    pad = (Phat2dPad*) widget;
    //debug ("during map\n");

    GTK_WIDGET_CLASS (parent_class)->map (widget);

    gtk_widget_queue_draw (widget);
    //debug ("after map\n");

}


static void phat_2d_pad_unmap (GtkWidget *widget)
{
    Phat2dPad* pad;

    debug ("unmap\n");
     
    g_return_if_fail (PHAT_IS_2D_PAD(widget));
    pad = (Phat2dPad*) widget;
   
    GTK_WIDGET_CLASS (parent_class)->unmap (widget);
}


static void phat_2d_pad_size_allocate (GtkWidget* widget,
					      GtkAllocation* allocation)
{
    Phat2dPad* pad;
    pad = PHAT_2D_PAD(widget);

    g_return_if_fail (widget != NULL);
    g_return_if_fail (allocation != NULL);
    g_return_if_fail (PHAT_IS_2D_PAD(widget));

    debug ("size allocate\n");
     
    GTK_WIDGET_CLASS (parent_class)->size_allocate (widget, allocation);

    if (GTK_WIDGET_REALIZED (widget))
    {
	debug ("setting pixmap size\n");
	//if (pad->pixmap)
	  //  g_object_unref (pad->pixmap);

	/*
	pad->pixmap = gdk_pixmap_new (pad->drawing_area->window,
                           widget->allocation.width,
                           widget->allocation.height,
                           -1);
	gdk_draw_rectangle (pad->drawing_area->window,
                      widget->style->black_gc,
                      TRUE,
                      0, 0,
                      widget->allocation.width,
                      widget->allocation.height);
	*/
	/*gdk_window_move_resize (PHAT_2D_PAD(widget)->event_window,
				allocation->x,
				allocation->y,
				allocation->width,
				allocation->height);*/
    }
}

static gboolean phat_2d_pad_expose (GtkWidget*      widget,
					   GdkEventExpose* event)
{
    Phat2dPad* pad;
    GtkAllocation* a;
     
    g_return_val_if_fail (widget != NULL, FALSE);
    g_return_val_if_fail (PHAT_IS_2D_PAD(widget), FALSE);
    g_return_val_if_fail (event != NULL, FALSE);
    g_return_val_if_fail (GTK_WIDGET_DRAWABLE (widget), FALSE);
    g_return_val_if_fail (event->count == 0, FALSE);

    debug ("expose\n");

    pad = PHAT_2D_PAD(widget);
    a = &widget->allocation;

    gdk_draw_drawable (widget->window,
                     widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                     pad->pixmap,
                     event->area.x, event->area.y,
                     event->area.x, event->area.y,
                     event->area.width, event->area.height);
   
        //GTK_WIDGET_CLASS (parent_class)->expose_event (widget, event);
    
 
    return TRUE;
}

/* Create a new backing pixmap of the appropriate size */
static gboolean phat_2d_pad_configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
    Phat2dPad* pad;

    debug ("configure  \n");
    pad = PHAT_2D_PAD(widget);
    if (pad->pixmap)
	g_object_unref (pad->pixmap);

    pad->pixmap = gdk_pixmap_new (widget->window,
			       widget->allocation.width,
			       widget->allocation.height,
			       -1);
    gdk_draw_rectangle (pad->pixmap,
			  widget->style->black_gc,
			  TRUE,
			  0, 0,
			  widget->allocation.width,
			  widget->allocation.height);

    return TRUE;
}


static gboolean phat_2d_pad_button_press (GtkWidget* widget,
						 GdkEventButton* event)
{
    Phat2dPad* pad = PHAT_2D_PAD(widget);

    debug ("pad press\n");
     
    if (event->type != GDK_BUTTON_PRESS)
	return FALSE;

    if (event->button == 1 && pad->pixmap != NULL) {
	gdouble pressure;
	gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_PRESSURE, &pressure);
	//draw_brush (widget, event->device->source, event->x, event->y, pressure);
    }

  return TRUE;

}


static gboolean phat_2d_pad_motion_notify (GtkWidget* widget,
						  GdkEventMotion* event)
{
    //Phat2dPad* pad = PHAT_2D_PAD(widget);

    gdouble x, y;
    gdouble pressure;
    GdkModifierType state;

    debug ("motion\n");

    if (event->is_hint) 
    {
	gdk_device_get_state (event->device, event->window, NULL, &state);
	gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_X, &x);
	gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_Y, &y);
	gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_PRESSURE, &pressure);
    }
    else
    {
	x = event->x;
	y = event->y;
	gdk_event_get_axis ((GdkEvent *)event, GDK_AXIS_PRESSURE, &pressure);
	state = event->state;
    }
	
    printf("pressure %f x %f y %f\n", pressure, x, y);
    //if (state & GDK_BUTTON1_MASK && widget->pixmap != NULL)
	//draw_brush (widget, event->device->source, x, y, pressure);
      
    return TRUE;
}
