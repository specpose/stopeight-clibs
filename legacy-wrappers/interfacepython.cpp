#include "interfacepython.h"
#include <iostream>

PyObject* legacy_wrappers::error(const char* message) {
	PyErr_SetString(legacy_wrappers::LegacyError, message);
	return NULL;
}

PyObject* legacy_wrappers::error(legacy::alg_logic_error err) {
	std::string message = std::string();
	message += err.fi_name;
	message += "::";
	message += err.fu_name;
	message += ": ";
	message += err.what();
	return legacy_wrappers::error(message.c_str());
}

PyObject* legacy_wrappers::convert(ListBase<dpoint> list) {
	PyObject* parray = PyList_New(list.size());
	for (int i = 0; i < list.size(); i++) {
		dpoint qpoint = list.at(i);
		PyObject* ppoint = Py_BuildValue("ff", qpoint.x(), qpoint.y());
		PyList_SetItem(parray, i, ppoint);
	}
	return parray;
}

PyObject* legacy_wrappers::parse_file(PyObject *self, PyObject *args) {
	const char *pythonpath;
	if (!PyArg_ParseTuple(args, "s", &pythonpath)) {
		return legacy_wrappers::error("Filename is not a list");
	}
	ListBase<dpoint> myList = ListBase<dpoint>();
	try {
		myList = myList.open(pythonpath);
	}
	catch (legacy::alg_logic_error exc) {
		return legacy_wrappers::error(exc);
	}
	catch (const char* text) {
		return legacy_wrappers::error(text);
	}
	catch (...) {
		return legacy_wrappers::error("undefined");
	}
	std::cout << "Loaded " << myList.size() << " points from file " << pythonpath << "\n";
	return legacy_wrappers::convert(myList);
}

ListBase<dpoint> legacy_wrappers::parse_list(PyObject *self, PyObject *args) {
	PyObject* obj;
	ListBase<dpoint> list = ListBase<dpoint>();
	if (!PyArg_ParseTuple(args, "O", &obj)) {
		throw std::exception("Argument is supposed to be a list of a pair of numbers");
	}
	PyObject* pyList = PySequence_Fast(obj, "Not a list");
	int length = PySequence_Size(obj);
	for (int i = 0; i < length; i++) {
		PyObject* item = PySequence_Fast_GET_ITEM(pyList, i);
		if (PySequence_Size(item) != 2) {
			throw std::exception("Malformed point format");
		}
		float xValue;
		float yValue;
		if (PyArg_ParseTuple(item, "ff", &xValue, &yValue)) {
			list << dpoint(xValue, yValue);
		}
		else {
			throw std::exception("Malformed number format");
		}
	}
	return list;
}

PyObject* legacy_wrappers::stroke_parallel(PyObject *self, PyObject *args) {
	EditorSpirals editor = EditorSpirals();

	try {
		editor.automatic(legacy_wrappers::parse_list(self, args));
	}
	catch (legacy::alg_logic_error exc) {
		return legacy_wrappers::error(exc);
	}
	catch (const char* text) {
		return legacy_wrappers::error(text);
	}
	catch (...) {
		return legacy_wrappers::error("undefined");
	}

	ListCopyable<dpoint> result = ListCopyable<dpoint>();
	result = editor.getOutput();
	return legacy_wrappers::convert(result);
}

PyObject* legacy_wrappers::stroke_sequential(PyObject *self, PyObject *args) {
	EditorCliffs editor = EditorCliffs();

	try {
		editor.automatic(legacy_wrappers::parse_list(self, args));
	}
	catch (legacy::alg_logic_error exc) {
		return legacy_wrappers::error(exc);
	}
	catch (const char* text) {
		return legacy_wrappers::error(text);
	}
	catch (...) {
		return legacy_wrappers::error("undefined");
	}

	ListCopyable<dpoint> result = ListCopyable<dpoint>();
	result = editor.getOutput();
	return legacy_wrappers::convert(result);

}

PyMODINIT_FUNC initstopeight_clibs_legacy(void)
{
	PyObject* my_mod = Py_InitModule("stopeight_clibs_legacy", stopeight_clibs_legacyMethods);
	if (my_mod == NULL)
		return;

	legacy_wrappers::LegacyError = PyErr_NewException((char*)("stopeight_clibs_legacy.error"), NULL, NULL);
	Py_INCREF(legacy_wrappers::LegacyError);
	PyModule_AddObject(my_mod, "error", legacy_wrappers::LegacyError);

}
