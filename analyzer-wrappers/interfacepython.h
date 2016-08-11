#ifndef INTERFACEPYTHON_H
#define INTERFACEPYTHON_H

#ifdef _WIN32
#ifdef _DEBUG
#undef _DEBUG
#define DEBUG_BYPASS 1
#endif
#endif

#include <Python.h>
#include "test.h"

namespace analyzer_wrappers{
	static PyObject* AnalyzerError;
	static PyObject* error(const char* message);
	static PyObject* hello(PyObject* self, PyObject* args);
}

static PyMethodDef stopeight_clibs_analyzerMethods[] = {
	{ "hello",  analyzer_wrappers::hello, METH_VARARGS,
	"Print hello world." },
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initstopeight_clibs_analyzer(void);

#ifdef DEBUG_BYPASS
#undef DEBUG_BYPASS
#define _DEBUG 1
#endif // DEBUG_BYPASS


#endif // INTERFACEPYTHON_H
