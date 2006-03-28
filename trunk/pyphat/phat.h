# 1 "/usr/include/phat/phat.h"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "/usr/include/phat/phat.h"



# 1 "/usr/include/phat/phatvfanslider.h" 1 3 4




# 1 "/usr/include/phat/phatfanslider.h" 1 3 4





G_BEGIN_DECLS







typedef struct _PhatFanSliderClass PhatFanSliderClass;
typedef struct _PhatFanSlider PhatFanSlider;

struct _PhatFanSlider
{
     GtkWidget parent;

     GtkAdjustment* adjustment;
     double val;
     double center_val;
     int xclick_root;
     int yclick_root;
     int xclick;
     int yclick;
     int fan_max_thickness;
     int state;
     gboolean inverted;
     GtkOrientation orientation;
     GtkWidget* fan_window;
     GdkRegion* fan_clip0;
     GdkRegion* fan_clip1;
     GdkCursor* arrow_cursor;
     GdkCursor* empty_cursor;
     GdkWindow* event_window;
     GtkWidget* hint_window0;
     GtkWidget* hint_window1;
     GdkRegion* hint_clip0;
     GdkRegion* hint_clip1;
};

struct _PhatFanSliderClass
{
     GtkWidgetClass parent_class;

     void (*value_changed) (PhatFanSlider* slider);
     void (*changed) (PhatFanSlider* slider);
};

GType phat_fan_slider_get_type ( );

void phat_fan_slider_set_value (PhatFanSlider* slider, double value);

double phat_fan_slider_get_value (PhatFanSlider* slider);

void phat_fan_slider_set_range (PhatFanSlider* slider,
          double lower, double upper);

void phat_fan_slider_get_range (PhatFanSlider* slider,
          double* lower, double* upper);

void phat_fan_slider_set_adjustment (PhatFanSlider* slider,
        GtkAdjustment* adjustment);

GtkAdjustment* phat_fan_slider_get_adjustment (PhatFanSlider* slider);

void phat_fan_slider_set_inverted (PhatFanSlider* slider, gboolean inverted);

gboolean phat_fan_slider_get_inverted (PhatFanSlider* slider);

G_END_DECLS
# 6 "/usr/include/phat/phatvfanslider.h" 2 3 4

G_BEGIN_DECLS







typedef struct _PhatVFanSliderClass PhatVFanSliderClass;
typedef struct _PhatVFanSlider PhatVFanSlider;

struct _PhatVFanSlider
{
     PhatFanSlider parent;
};

struct _PhatVFanSliderClass
{
     PhatFanSliderClass parent_class;
};

GType phat_vfan_slider_get_type ( );

GtkWidget* phat_vfan_slider_new (GtkAdjustment* adjustment);

GtkWidget* phat_vfan_slider_new_with_range (double value,
         double lower,
         double upper,
         double step);
G_END_DECLS
# 5 "/usr/include/phat/phat.h" 2
# 1 "/usr/include/phat/phathfanslider.h" 1 3 4






G_BEGIN_DECLS







typedef struct _PhatHFanSliderClass PhatHFanSliderClass;
typedef struct _PhatHFanSlider PhatHFanSlider;

struct _PhatHFanSlider
{
     PhatFanSlider parent;
};

struct _PhatHFanSliderClass
{
     PhatFanSliderClass parent_class;
};

GType phat_hfan_slider_get_type ( );

GtkWidget* phat_hfan_slider_new (GtkAdjustment* adjustment);

GtkWidget* phat_hfan_slider_new_with_range (double value,
         double lower,
         double upper,
         double step);
G_END_DECLS
# 6 "/usr/include/phat/phat.h" 2

# 1 "/usr/include/phat/phatsliderbutton.h" 1 3 4





G_BEGIN_DECLS







typedef struct _PhatSliderButtonClass PhatSliderButtonClass;
typedef struct _PhatSliderButton PhatSliderButton;

struct _PhatSliderButton
{
    GtkHBox parent;

    GdkCursor* arrow_cursor;
    GdkCursor* empty_cursor;
    GdkWindow* event_window;
    GtkWidget* left_arrow;
    GtkWidget* right_arrow;
    GtkWidget* label;
    GtkWidget* prefix_label;
    GtkWidget* postfix_label;
    GtkWidget* entry;
    GtkAdjustment* adjustment;
    char* prefix;
    char* postfix;
    int digits;
    int hilite;
    int state;
    int xpress_root, ypress_root;
    int xpress, ypress;
    guint threshold;
    gboolean slid;
};

struct _PhatSliderButtonClass
{
    GtkHBoxClass parent_class;

    void (*value_changed) (PhatSliderButton* slider);
    void (*changed) (PhatSliderButton* slider);
};

GType phat_slider_button_get_type ( );

GtkWidget* phat_slider_button_new (GtkAdjustment* adjustment,
       int digits);

GtkWidget* phat_slider_button_new_with_range (double value,
           double lower,
           double upper,
           double step,
           int digits);

void phat_slider_button_set_value (PhatSliderButton* button, double value);

double phat_slider_button_get_value (PhatSliderButton* button);

void phat_slider_button_set_range (PhatSliderButton* button,
       double lower, double upper);

void phat_slider_button_get_range (PhatSliderButton* button,
       double* lower, double* upper);

void phat_slider_button_set_adjustment (PhatSliderButton* button,
     GtkAdjustment* adjustment);

GtkAdjustment* phat_slider_button_get_adjustment (PhatSliderButton* button);

void phat_slider_button_set_increment (PhatSliderButton* button,
           double step, double page);

void phat_slider_button_get_increment (PhatSliderButton* button,
           double* step, double* page);

void phat_slider_button_set_format (PhatSliderButton* button,
        int digits,
        const char* prefix,
        const char* postfix);

void phat_slider_button_get_format (PhatSliderButton* button,
        int* digits,
        char** prefix,
        char** postfix);

void phat_slider_button_set_threshold (PhatSliderButton* button,
           guint threshold);

int phat_slider_button_get_threshold (PhatSliderButton* button);

G_END_DECLS
# 8 "/usr/include/phat/phat.h" 2
# 1 "/usr/include/phat/phatkeyboard.h" 1 3 4






G_BEGIN_DECLS







typedef struct _PhatKeyboardClass PhatKeyboardClass;
typedef struct _PhatKeyboard PhatKeyboard;
typedef struct __Key _Key;


enum
{
    PHAT_KEYBOARD_KEY_WIDTH = 13,
    PHAT_KEYBOARD_KEY_LENGTH = 33,
};


struct __Key
{
    int index;
    PhatKeyboard* keyboard;
    GnomeCanvasGroup* group;
    GnomeCanvasItem* pre;
    GnomeCanvasItem* on;
    GnomeCanvasItem* shad;
};

struct _PhatKeyboard
{

    GtkViewport parent;

    _Key *keys;
    int nkeys;
    int label;
    GnomeCanvas* canvas;
    GtkOrientation orientation;
};

struct _PhatKeyboardClass
{

    GtkViewportClass parent_class;

    void (*key_pressed)(PhatKeyboard* keyboard, int key);
    void (*key_released)(PhatKeyboard* keyboard, int key);
};

GType phat_keyboard_get_type(void);
GtkAdjustment* phat_keyboard_get_adjustment(PhatKeyboard* keyboard);
void phat_keyboard_set_adjustment(PhatKeyboard* keyboard, GtkAdjustment* adjustment);

G_END_DECLS
# 9 "/usr/include/phat/phat.h" 2
# 1 "/usr/include/phat/phatvkeyboard.h" 1 3 4






G_BEGIN_DECLS







typedef struct _PhatVKeyboardClass PhatVKeyboardClass;
typedef struct _PhatVKeyboard PhatVKeyboard;

struct _PhatVKeyboard
{

    PhatKeyboard parent;
};

struct _PhatVKeyboardClass
{

    PhatKeyboardClass parent_class;
};

GType phat_vkeyboard_get_type(void);
GtkWidget* phat_vkeyboard_new(GtkAdjustment* adjustment, int numkeys, gboolean show_labels);

G_END_DECLS
# 10 "/usr/include/phat/phat.h" 2
# 1 "/usr/include/phat/phathkeyboard.h" 1 3 4






G_BEGIN_DECLS







typedef struct _PhatHKeyboardClass PhatHKeyboardClass;
typedef struct _PhatHKeyboard PhatHKeyboard;

struct _PhatHKeyboard
{

    PhatKeyboard parent;
};

struct _PhatHKeyboardClass
{

    PhatKeyboardClass parent_class;
};

GType phat_hkeyboard_get_type(void);
GtkWidget* phat_hkeyboard_new(GtkAdjustment* adjustment, int numkeys, gboolean show_labels);

G_END_DECLS
# 11 "/usr/include/phat/phat.h" 2
# 1 "/usr/include/phat/phatpad.h" 1 3 4





G_BEGIN_DECLS







typedef struct _PhatPadClass PhatPadClass;
typedef struct _PhatPad PhatPad;

struct _PhatPad
{
    GtkDrawingArea parent;
    GdkPixmap* pixmap;
    GtkAdjustment* pressure;
    gboolean p_is_log;
    GtkAdjustment* xtilt;
    gboolean xt_is_log;
    GtkAdjustment* ytilt;
    gboolean yt_is_log;
    GtkAdjustment* x;
    gboolean x_is_log;
    GtkAdjustment* y;
    gboolean y_is_log;
};

struct _PhatPadClass
{
    GtkDrawingAreaClass parent_class;

    void (*value_changed) (PhatPad* pad);
};

GType phat_pad_get_type ( );


GtkWidget* phat_pad_new ( );
GtkAdjustment* phat_pad_get_ytilt (PhatPad* pad);
GtkAdjustment* phat_pad_get_xtilt (PhatPad* pad);
GtkAdjustment* phat_pad_get_pressure (PhatPad* pad);
GtkAdjustment* phat_pad_get_y (PhatPad* pad);
GtkAdjustment* phat_pad_get_x (PhatPad* pad);
void phat_pad_set_x_range (PhatPad* pad, gdouble min, gdouble max);
void phat_pad_set_y_range (PhatPad* pad, gdouble min, gdouble max);
void phat_pad_set_pressure_range (PhatPad* pad, gdouble min, gdouble max);
void phat_pad_set_x_log (PhatPad* pad, gboolean is_log);
void phat_pad_set_y_log (PhatPad* pad, gboolean is_log);
void phat_pad_set_pressure_log (PhatPad* pad, gboolean is_log);

G_END_DECLS
# 12 "/usr/include/phat/phat.h" 2
