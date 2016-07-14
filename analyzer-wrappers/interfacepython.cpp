#include "interfacepython.h"

PyMODINIT_FUNC initstopeight_clibs_analyzer(void)
{
    (void) Py_InitModule("stopeight_clibs_analyzer", stopeight_clibs_analyzerMethods);
}
