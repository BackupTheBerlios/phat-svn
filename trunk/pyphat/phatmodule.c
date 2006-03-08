#include <pygobject.h>
 
void phat_register_classes (PyObject *d); 
extern PyMethodDef phat_functions[];
 
DL_EXPORT(void)

initphat(void)
{
    PyObject *m, *d;
    //PyObject *e;
 
    init_pygobject ();
 
    m = Py_InitModule ("phat", phat_functions);
    d = PyModule_GetDict (m);
 
    phat_register_classes (d);
 
    if (PyErr_Occurred ()) {
	
	PyErr_Print();
        Py_FatalError ("can't initialise module phat");
    }
}
