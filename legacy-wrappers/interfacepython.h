#ifndef INTERFACEPYTHON_H
#define INTERFACEPYTHON_H

#include "listbase.h"
#include "editorspirals.h"
#include <Python.h>

namespace legacy_wrappers{
//private
static PyObject* convert(ListBase<dpoint> list);
ListBase<dpoint> parse_list(PyObject *self, PyObject *args);
//public
static PyObject* parse_file(PyObject* self, PyObject* args);
static PyObject* stroke_parallel(PyObject* self, PyObject* args);
}

static PyMethodDef stopeight_clibs_legacyMethods[] = {
    {"parse_file",  legacy_wrappers::parse_file, METH_VARARGS,
     "parse proprietary legacy qt file format for input points of recorded pen-stroke."},
    {"stroke_parallel",  legacy_wrappers::stroke_parallel, METH_VARARGS,
     "This is the parallel version of the stroke analyzer. It can look ahead, detect and center multiple immediately repeating features, when the number of features is prime. It will theoretically run out of memory if the number of immediately repeating features is too high."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initstopeight_clibs_legacy(void);

#endif // INTERFACEPYTHON_H
