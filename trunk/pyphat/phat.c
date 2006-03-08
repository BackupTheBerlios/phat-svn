/* -- THIS FILE IS GENERATED - DO NOT EDIT *//* -*- Mode: C; c-basic-offset: 4 -*- */

#include <Python.h>



#line 3 "phat.override"
#include <Python.h>               
#include "pygobject.h"
#include <phat/phat.h>
#line 12 "phat.c"


/* ---------- types from other modules ---------- */
static PyTypeObject *_PyGtkWidget_Type;
#define PyGtkWidget_Type (*_PyGtkWidget_Type)
static PyTypeObject *_PyGtkAdjustment_Type;
#define PyGtkAdjustment_Type (*_PyGtkAdjustment_Type)
static PyTypeObject *_PyGtkViewport_Type;
#define PyGtkViewport_Type (*_PyGtkViewport_Type)
static PyTypeObject *_PyGtkHBox_Type;
#define PyGtkHBox_Type (*_PyGtkHBox_Type)


/* ---------- forward type declarations ---------- */
PyTypeObject PyPhatFanSlider_Type;
PyTypeObject PyPhatHFanSlider_Type;
PyTypeObject PyPhatKeyboard_Type;
PyTypeObject PyPhatHKeyboard_Type;
PyTypeObject PyPhatSliderButton_Type;
PyTypeObject PyPhatVFanSlider_Type;
PyTypeObject PyPhatVKeyboard_Type;


/* ----------- PhatFanSlider ----------- */

static PyObject *
_wrap_phat_fan_slider_set_value(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "value", NULL };
    double value;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "d:PhatFanSlider.set_value", kwlist, &value))
        return NULL;
    phat_fan_slider_set_value(PHAT_FAN_SLIDER(self->obj), value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_fan_slider_get_value(PyGObject *self)
{
    double ret;

    ret = phat_fan_slider_get_value(PHAT_FAN_SLIDER(self->obj));
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_phat_fan_slider_set_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "lower", "upper", NULL };
    double lower, upper;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:PhatFanSlider.set_range", kwlist, &lower, &upper))
        return NULL;
    phat_fan_slider_set_range(PHAT_FAN_SLIDER(self->obj), lower, upper);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_fan_slider_set_adjustment(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "adjustment", NULL };
    PyGObject *adjustment;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:PhatFanSlider.set_adjustment", kwlist, &PyGtkAdjustment_Type, &adjustment))
        return NULL;
    phat_fan_slider_set_adjustment(PHAT_FAN_SLIDER(self->obj), GTK_ADJUSTMENT(adjustment->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_fan_slider_get_adjustment(PyGObject *self)
{
    GtkAdjustment *ret;

    ret = phat_fan_slider_get_adjustment(PHAT_FAN_SLIDER(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_phat_fan_slider_set_inverted(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "inverted", NULL };
    int inverted;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i:PhatFanSlider.set_inverted", kwlist, &inverted))
        return NULL;
    phat_fan_slider_set_inverted(PHAT_FAN_SLIDER(self->obj), inverted);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_fan_slider_get_inverted(PyGObject *self)
{
    int ret;

    ret = phat_fan_slider_get_inverted(PHAT_FAN_SLIDER(self->obj));
    return PyBool_FromLong(ret);

}

static PyMethodDef _PyPhatFanSlider_methods[] = {
    { "set_value", (PyCFunction)_wrap_phat_fan_slider_set_value, METH_VARARGS|METH_KEYWORDS },
    { "get_value", (PyCFunction)_wrap_phat_fan_slider_get_value, METH_NOARGS },
    { "set_range", (PyCFunction)_wrap_phat_fan_slider_set_range, METH_VARARGS|METH_KEYWORDS },
    { "set_adjustment", (PyCFunction)_wrap_phat_fan_slider_set_adjustment, METH_VARARGS|METH_KEYWORDS },
    { "get_adjustment", (PyCFunction)_wrap_phat_fan_slider_get_adjustment, METH_NOARGS },
    { "set_inverted", (PyCFunction)_wrap_phat_fan_slider_set_inverted, METH_VARARGS|METH_KEYWORDS },
    { "get_inverted", (PyCFunction)_wrap_phat_fan_slider_get_inverted, METH_NOARGS },
    { NULL, NULL, 0 }
};

PyTypeObject PyPhatFanSlider_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "phat.FanSlider",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyPhatFanSlider_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- PhatHFanSlider ----------- */

PyTypeObject PyPhatHFanSlider_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "phat.HFanSlider",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    NULL,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- PhatKeyboard ----------- */

static PyObject *
_wrap_phat_keyboard_get_adjustment(PyGObject *self)
{
    GtkAdjustment *ret;

    ret = phat_keyboard_get_adjustment(PHAT_KEYBOARD(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_phat_keyboard_set_adjustment(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "adjustment", NULL };
    PyGObject *adjustment;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:PhatKeyboard.set_adjustment", kwlist, &PyGtkAdjustment_Type, &adjustment))
        return NULL;
    phat_keyboard_set_adjustment(PHAT_KEYBOARD(self->obj), GTK_ADJUSTMENT(adjustment->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _PyPhatKeyboard_methods[] = {
    { "get_adjustment", (PyCFunction)_wrap_phat_keyboard_get_adjustment, METH_NOARGS },
    { "set_adjustment", (PyCFunction)_wrap_phat_keyboard_set_adjustment, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

PyTypeObject PyPhatKeyboard_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "phat.Keyboard",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyPhatKeyboard_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- PhatHKeyboard ----------- */

PyTypeObject PyPhatHKeyboard_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "phat.HKeyboard",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    NULL,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- PhatSliderButton ----------- */

static int
_wrap_phat_slider_button_new(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "adjustment", "digits", NULL };
    PyGObject *adjustment;
    int digits;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i:PhatSliderButton.__init__", kwlist, &PyGtkAdjustment_Type, &adjustment, &digits))
        return -1;
    self->obj = (GObject *)phat_slider_button_new(GTK_ADJUSTMENT(adjustment->obj), digits);

    if (!self->obj) {
        PyErr_SetString(PyExc_RuntimeError, "could not create PhatSliderButton object");
        return -1;
    }
    pygobject_register_wrapper((PyObject *)self);
    return 0;
}

static PyObject *
_wrap_phat_slider_button_set_value(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "value", NULL };
    double value;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "d:PhatSliderButton.set_value", kwlist, &value))
        return NULL;
    phat_slider_button_set_value(PHAT_SLIDER_BUTTON(self->obj), value);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_slider_button_get_value(PyGObject *self)
{
    double ret;

    ret = phat_slider_button_get_value(PHAT_SLIDER_BUTTON(self->obj));
    return PyFloat_FromDouble(ret);
}

static PyObject *
_wrap_phat_slider_button_set_range(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "lower", "upper", NULL };
    double lower, upper;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:PhatSliderButton.set_range", kwlist, &lower, &upper))
        return NULL;
    phat_slider_button_set_range(PHAT_SLIDER_BUTTON(self->obj), lower, upper);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_slider_button_set_adjustment(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "adjustment", NULL };
    PyGObject *adjustment;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!:PhatSliderButton.set_adjustment", kwlist, &PyGtkAdjustment_Type, &adjustment))
        return NULL;
    phat_slider_button_set_adjustment(PHAT_SLIDER_BUTTON(self->obj), GTK_ADJUSTMENT(adjustment->obj));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_slider_button_get_adjustment(PyGObject *self)
{
    GtkAdjustment *ret;

    ret = phat_slider_button_get_adjustment(PHAT_SLIDER_BUTTON(self->obj));
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_phat_slider_button_set_increment(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "step", "page", NULL };
    double step, page;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dd:PhatSliderButton.set_increment", kwlist, &step, &page))
        return NULL;
    phat_slider_button_set_increment(PHAT_SLIDER_BUTTON(self->obj), step, page);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_slider_button_set_format(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "digits", "prefix", "postfix", NULL };
    int digits;
    char *prefix, *postfix;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iss:PhatSliderButton.set_format", kwlist, &digits, &prefix, &postfix))
        return NULL;
    phat_slider_button_set_format(PHAT_SLIDER_BUTTON(self->obj), digits, prefix, postfix);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_slider_button_set_threshold(PyGObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "threshold", NULL };
    guint threshold;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "I:PhatSliderButton.set_threshold", kwlist, &threshold))
        return NULL;
    phat_slider_button_set_threshold(PHAT_SLIDER_BUTTON(self->obj), threshold);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
_wrap_phat_slider_button_get_threshold(PyGObject *self)
{
    int ret;

    ret = phat_slider_button_get_threshold(PHAT_SLIDER_BUTTON(self->obj));
    return PyInt_FromLong(ret);
}

static PyMethodDef _PyPhatSliderButton_methods[] = {
    { "set_value", (PyCFunction)_wrap_phat_slider_button_set_value, METH_VARARGS|METH_KEYWORDS },
    { "get_value", (PyCFunction)_wrap_phat_slider_button_get_value, METH_NOARGS },
    { "set_range", (PyCFunction)_wrap_phat_slider_button_set_range, METH_VARARGS|METH_KEYWORDS },
    { "set_adjustment", (PyCFunction)_wrap_phat_slider_button_set_adjustment, METH_VARARGS|METH_KEYWORDS },
    { "get_adjustment", (PyCFunction)_wrap_phat_slider_button_get_adjustment, METH_NOARGS },
    { "set_increment", (PyCFunction)_wrap_phat_slider_button_set_increment, METH_VARARGS|METH_KEYWORDS },
    { "set_format", (PyCFunction)_wrap_phat_slider_button_set_format, METH_VARARGS|METH_KEYWORDS },
    { "set_threshold", (PyCFunction)_wrap_phat_slider_button_set_threshold, METH_VARARGS|METH_KEYWORDS },
    { "get_threshold", (PyCFunction)_wrap_phat_slider_button_get_threshold, METH_NOARGS },
    { NULL, NULL, 0 }
};

PyTypeObject PyPhatSliderButton_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "phat.SliderButton",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    _PyPhatSliderButton_methods,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)_wrap_phat_slider_button_new,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- PhatVFanSlider ----------- */

PyTypeObject PyPhatVFanSlider_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "phat.VFanSlider",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    NULL,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- PhatVKeyboard ----------- */

PyTypeObject PyPhatVKeyboard_Type = {
    PyObject_HEAD_INIT(NULL)
    0,					/* ob_size */
    "phat.VKeyboard",			/* tp_name */
    sizeof(PyGObject),	        /* tp_basicsize */
    0,					/* tp_itemsize */
    /* methods */
    (destructor)0,	/* tp_dealloc */
    (printfunc)0,			/* tp_print */
    (getattrfunc)0,	/* tp_getattr */
    (setattrfunc)0,	/* tp_setattr */
    (cmpfunc)0,		/* tp_compare */
    (reprfunc)0,		/* tp_repr */
    (PyNumberMethods*)0,     /* tp_as_number */
    (PySequenceMethods*)0, /* tp_as_sequence */
    (PyMappingMethods*)0,   /* tp_as_mapping */
    (hashfunc)0,		/* tp_hash */
    (ternaryfunc)0,		/* tp_call */
    (reprfunc)0,		/* tp_str */
    (getattrofunc)0,	/* tp_getattro */
    (setattrofunc)0,	/* tp_setattro */
    (PyBufferProcs*)0,	/* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                      /* tp_flags */
    NULL, 				/* Documentation string */
    (traverseproc)0,	/* tp_traverse */
    (inquiry)0,		/* tp_clear */
    (richcmpfunc)0,	/* tp_richcompare */
    offsetof(PyGObject, weakreflist),             /* tp_weaklistoffset */
    (getiterfunc)0,		/* tp_iter */
    (iternextfunc)0,	/* tp_iternext */
    NULL,			/* tp_methods */
    0,					/* tp_members */
    0,		       	/* tp_getset */
    NULL,				/* tp_base */
    NULL,				/* tp_dict */
    (descrgetfunc)0,	/* tp_descr_get */
    (descrsetfunc)0,	/* tp_descr_set */
    offsetof(PyGObject, inst_dict),                 /* tp_dictoffset */
    (initproc)0,		/* tp_init */
    (allocfunc)0,           /* tp_alloc */
    (newfunc)0,               /* tp_new */
    (freefunc)0,             /* tp_free */
    (inquiry)0              /* tp_is_gc */
};



/* ----------- functions ----------- */

static PyObject *
_wrap_phat_vfan_slider_new_with_range(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "value", "lower", "upper", "step", NULL };
    double value, lower, upper, step;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:phat_vfan_slider_new_with_range", kwlist, &value, &lower, &upper, &step))
        return NULL;
    ret = phat_vfan_slider_new_with_range(value, lower, upper, step);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_phat_hfan_slider_new_with_range(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "value", "lower", "upper", "step", NULL };
    double value, lower, upper, step;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "dddd:phat_hfan_slider_new_with_range", kwlist, &value, &lower, &upper, &step))
        return NULL;
    ret = phat_hfan_slider_new_with_range(value, lower, upper, step);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

static PyObject *
_wrap_phat_slider_button_new_with_range(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = { "value", "lower", "upper", "step", "digits", NULL };
    int digits;
    double value, lower, upper, step;
    GtkWidget *ret;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ddddi:phat_slider_button_new_with_range", kwlist, &value, &lower, &upper, &step, &digits))
        return NULL;
    ret = phat_slider_button_new_with_range(value, lower, upper, step, digits);
    /* pygobject_new handles NULL checking */
    return pygobject_new((GObject *)ret);
}

PyMethodDef phat_functions[] = {
    { "phat_vfan_slider_new_with_range", (PyCFunction)_wrap_phat_vfan_slider_new_with_range, METH_VARARGS|METH_KEYWORDS },
    { "phat_hfan_slider_new_with_range", (PyCFunction)_wrap_phat_hfan_slider_new_with_range, METH_VARARGS|METH_KEYWORDS },
    { "phat_slider_button_new_with_range", (PyCFunction)_wrap_phat_slider_button_new_with_range, METH_VARARGS|METH_KEYWORDS },
    { NULL, NULL, 0 }
};

/* initialise stuff extension classes */
void
phat_register_classes(PyObject *d)
{
    PyObject *module;

    if ((module = PyImport_ImportModule("gtk")) != NULL) {
        PyObject *moddict = PyModule_GetDict(module);

        _PyGtkWidget_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "Widget");
        if (_PyGtkWidget_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Widget from gtk");
            return;
        }
        _PyGtkAdjustment_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "Adjustment");
        if (_PyGtkAdjustment_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Adjustment from gtk");
            return;
        }
        _PyGtkViewport_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "Viewport");
        if (_PyGtkViewport_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name Viewport from gtk");
            return;
        }
        _PyGtkHBox_Type = (PyTypeObject *)PyDict_GetItemString(moddict, "HBox");
        if (_PyGtkHBox_Type == NULL) {
            PyErr_SetString(PyExc_ImportError,
                "cannot import name HBox from gtk");
            return;
        }
    } else {
        PyErr_SetString(PyExc_ImportError,
            "could not import gtk");
        return;
    }


#line 731 "phat.c"
    pygobject_register_class(d, "PhatFanSlider", PHAT_TYPE_FAN_SLIDER, &PyPhatFanSlider_Type, Py_BuildValue("(O)", &PyGtkWidget_Type));
    pygobject_register_class(d, "PhatHFanSlider", PHAT_TYPE_HFAN_SLIDER, &PyPhatHFanSlider_Type, Py_BuildValue("(O)", &PyPhatFanSlider_Type));
    pygobject_register_class(d, "PhatKeyboard", PHAT_TYPE_KEYBOARD, &PyPhatKeyboard_Type, Py_BuildValue("(O)", &PyGtkViewport_Type));
    pygobject_register_class(d, "PhatHKeyboard", PHAT_TYPE_HKEYBOARD, &PyPhatHKeyboard_Type, Py_BuildValue("(O)", &PyPhatKeyboard_Type));
    pygobject_register_class(d, "PhatSliderButton", PHAT_TYPE_SLIDER_BUTTON, &PyPhatSliderButton_Type, Py_BuildValue("(O)", &PyGtkHBox_Type));
    pygobject_register_class(d, "PhatVFanSlider", PHAT_TYPE_VFAN_SLIDER, &PyPhatVFanSlider_Type, Py_BuildValue("(O)", &PyPhatFanSlider_Type));
    pygobject_register_class(d, "PhatVKeyboard", PHAT_TYPE_VKEYBOARD, &PyPhatVKeyboard_Type, Py_BuildValue("(O)", &PyPhatKeyboard_Type));
}
