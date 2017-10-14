#ifndef INTERFACEPYTHON_H
#define INTERFACEPYTHON_H

#include "error.h"
#include "test.h"


#ifdef _WINDOWS
#ifdef _DEBUG
#undef _DEBUG
#define DEBUG_BYPASS 1
#endif
#endif

#include <Python.h>

namespace analyzer_wrappers{
//private
	static PyObject* AnalyzerError;
	static PyObject* error(const char* message);
	static PyObject* error(analyzer::alg_logic_error err);
//public
	static PyObject* hello(PyObject* self, PyObject* args);
}

static PyMethodDef analyzerMethods[] = {
	{ "hello",  analyzer_wrappers::hello, METH_VARARGS,
	"Print hello world." },
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

#ifdef PY_MAJOR_VERSION
#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef analyzermodule = {
	PyModuleDef_HEAD_INIT,
        "analyzer",   /* name of module */
	NULL, /* module documentation, may be NULL */
	-1,       /* size of per-interpreter state of the module,
			  or -1 if the module keeps state in global variables. */
        analyzerMethods
};

PyMODINIT_FUNC PyInit_analyzer(void);

#else // PY_MAJOR_VERSION >= 3

PyMODINIT_FUNC initanalyzer(void);

#endif // PY_MAJOR_VERSION >= 3
#endif // PY_MAJOR_VERSION

#ifdef DEBUG_BYPASS
#undef DEBUG_BYPASS
#define _DEBUG 1
#endif // DEBUG_BYPASS

#endif // INTERFACEPYTHON_H
