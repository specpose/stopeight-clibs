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
static PyObject* stroke_spirals(PyObject* self, PyObject* args);
}

static PyMethodDef stopeight_clibs_legacyMethods[] = {
    {"parse_file",  legacy_wrappers::parse_file, METH_VARARGS,
     "parse proprietary legacy qt file format for input points of recorded pen-stroke."},
    {"stroke_spirals",  legacy_wrappers::stroke_spirals, METH_VARARGS,
     "detect spirals in pen-stroke."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initstopeight_clibs_legacy(void);

#endif // INTERFACEPYTHON_H
