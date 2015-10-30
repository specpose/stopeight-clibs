#ifndef INTERFACEPYTHON_H
#define INTERFACEPYTHON_H

#include "listbase.h"
#include <Python.h>

namespace legacy_wrappers{
//private
static PyObject* convert(ListBase<dpoint> list);
//public
static PyObject* parse_file(PyObject* self, PyObject* args);
}

static PyMethodDef stopeight_clibs_legacyMethods[] = {
    {"parse_file",  legacy_wrappers::parse_file, METH_VARARGS,
     "parse proprietary legacy qt file format for input points of recorded pen-stroke."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initstopeight_clibs_legacy(void);

#endif // INTERFACEPYTHON_H
