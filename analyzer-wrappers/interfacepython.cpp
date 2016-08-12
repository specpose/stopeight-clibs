#include "interfacepython.h"
#include <iostream>

PyObject* analyzer_wrappers::error(const char* message) {
	PyErr_SetString(analyzer_wrappers::AnalyzerError, message);
	return NULL;
}

PyObject* analyzer_wrappers::error(analyzer::alg_logic_error err) {
	std::string message = std::string();
	message += err.fi_name;
	message += "::";
	message += err.fu_name;
	message += ": ";
	message += err.what();
	return analyzer_wrappers::error(message.c_str());
}

PyObject* analyzer_wrappers::hello(PyObject *self, PyObject *args) {
	const char *name;
	if (PyArg_ParseTuple(args, "s", &name)) {
		try {
			Test tester = Test();
			tester.hello(name);
			return 0;
		}
		catch (analyzer::alg_logic_error exc) {
			return analyzer_wrappers::error(exc);
		}
		catch (const char* text) {
			return analyzer_wrappers::error(text);
		}
		catch (...) {
			return analyzer_wrappers::error("undefined");
		}
	}
	else {
		return analyzer_wrappers::error("What is the name?");
	}
	return NULL;
}


PyMODINIT_FUNC initstopeight_clibs_analyzer(void)
{
	PyObject* my_mod = Py_InitModule("stopeight_clibs_analyzer", stopeight_clibs_analyzerMethods);
	if (my_mod == NULL)
		return;

	analyzer_wrappers::AnalyzerError = PyErr_NewException((char*)("stopeight_clibs_analyzer.error"), NULL, NULL);
	Py_INCREF(analyzer_wrappers::AnalyzerError);
	PyModule_AddObject(my_mod, "error", analyzer_wrappers::AnalyzerError);
}
