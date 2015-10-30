#include "interfacepython.h"

PyObject* legacy_wrappers::convert(ListBase<dpoint> list){
    PyObject* parray=PyList_New(list.size());
    for (int i=0;i<list.size();i++){
        dpoint qpoint = list.at(i);
        PyObject* ppoint = Py_BuildValue("ff",qpoint.x(),qpoint.y());
        PyList_SetItem(parray,i,ppoint);
    }
    return parray;
}

PyObject* legacy_wrappers::parse_file(PyObject *self, PyObject *args){
    const char *pythonpath;
    if (!PyArg_ParseTuple(args, "s", &pythonpath))
        return NULL;
    ListBase<dpoint> myList = ListBase<dpoint>();
    myList= myList.open(std::string(pythonpath));
    return legacy_wrappers::convert(myList);
}

PyMODINIT_FUNC initstopeight_clibs_legacy(void)
{
    (void) Py_InitModule("stopeight_clibs_legacy", stopeight_clibs_legacyMethods);
}
