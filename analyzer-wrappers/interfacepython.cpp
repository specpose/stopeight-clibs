#include "interfacepython.h"

PyObject* analyzer_wrappers::hello(PyObject *self, PyObject *args) {
	const char *name;
	if (PyArg_ParseTuple(args, "s", &name)) {
		printf("Hello from %s in hello\n", name);
		try {
			Test tester = Test();
			tester.hello(name);
			return 0;
		}
		catch (const char* text) {
			printf("Error in %s: %s\n", __func__, text);
			PyObject* error;
			PyErr_SetString(error, text);
			return error;
		}
		catch (...) {

			printf("Error in %s: %s\n", __func__, " undefined");
			PyObject* error;
			PyErr_SetNone(error);
			return error;
		}
	}
	return NULL;
}


PyMODINIT_FUNC initstopeight_clibs_analyzer(void)
{
    (void) Py_InitModule("stopeight_clibs_analyzer", stopeight_clibs_analyzerMethods);
}
