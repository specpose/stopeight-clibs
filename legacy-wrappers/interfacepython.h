#ifndef INTERFACEPYTHON_H
#define INTERFACEPYTHON_H

#include "listbase.h"
#include "editorspirals.h"
#include "editorcliffs.h"

#ifdef _WIN32
#ifdef _DEBUG
#undef _DEBUG
#define DEBUG_BYPASS 1
#endif
#endif

#include <Python.h>

namespace legacy_wrappers{
//private
static PyObject* convert(ListBase<dpoint> list);
ListBase<dpoint> parse_list(PyObject *self, PyObject *args);
//public
static PyObject* parse_file(PyObject* self, PyObject* args);
static PyObject* stroke_parallel(PyObject* self, PyObject* args);
static PyObject* stroke_sequential(PyObject* self, PyObject* args);
}

static PyMethodDef stopeight_clibs_legacyMethods[] = {
    {"parse_file",  legacy_wrappers::parse_file, METH_VARARGS,
     "parse proprietary legacy qt file format for input points of recorded pen-stroke."},
    {"stroke_parallel",  legacy_wrappers::stroke_parallel, METH_VARARGS,
     "This is the parallel version of the stroke analyzer. It can look ahead, detect and center multiple immediately repeating features, when the number of features is prime. It will theoretically run out of memory if the number of immediately repeating features is too high."},
    {"stroke_sequential",  legacy_wrappers::stroke_sequential, METH_VARARGS,
     "This is the sequential version of the stroke analyzer. It will subdivide pairs (cliffs) and triplets (turns) of immediately repeating features without further lookahead and center them."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initstopeight_clibs_legacy(void);

#ifdef DEBUG_BYPASS
#undef DEBUG_BYPASS
#define _DEBUG 1
#endif // DEBUG_BYPASS

#endif // INTERFACEPYTHON_H
