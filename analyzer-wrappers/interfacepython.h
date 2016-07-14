#ifndef INTERFACEPYTHON_H
#define INTERFACEPYTHON_H

#include <Python.h>

namespace analyzer_wrappers{

}

static PyMethodDef stopeight_clibs_analyzerMethods[] = {
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initstopeight_clibs_analyzer(void);

#endif // INTERFACEPYTHON_H
