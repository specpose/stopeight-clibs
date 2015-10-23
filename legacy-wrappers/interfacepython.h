#ifndef INTERFACEPYTHON_H
#define INTERFACEPYTHON_H

#include <string>
#include <Python.h>
//#include "numpy/ndarrayobject.h"

class interfacepython
{
public:
    interfacepython() {}
    virtual ~interfacepython();

    // First Argument is python file pointer
    virtual PyObject* parseFile(PyObject* self, PyObject* args);
};

#endif // INTERFACEPYTHON_H
