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
    if (!PyArg_ParseTuple(args, "s", &pythonpath)){
        printf("Error in %s: %s\n",__func__,"Filename is not a list");
        return NULL;
    }
    ListBase<dpoint> myList = ListBase<dpoint>();
    try {
        myList= myList.open(pythonpath);
    } catch (const char* text){
        printf("Error in %s: %s\n",__func__,text);
        PyObject* error;
        PyErr_SetString(error,text);
        return error;
    } catch (...){

        printf("Error in %s: %s\n",__func__," undefined");
        PyObject* error;
        PyErr_SetNone(error);
        return error;
    }
    printf("Loaded %d points from file: %s\n",myList.size(),pythonpath);
    return legacy_wrappers::convert(myList);
}

ListBase<dpoint> legacy_wrappers::parse_list(PyObject *self, PyObject *args) {
    PyObject* obj;
    ListBase<dpoint> list = ListBase<dpoint>();
    if (!PyArg_ParseTuple(args, "O", &obj)){
        printf("Error in %s: %s\n",__func__,"Argument is supposed to be a list of a pair of numbers");
        return list;
    }
    PyObject* pyList = PySequence_Fast(obj,"Not a list");
    int length = PySequence_Size(obj);
    for (int i=0;i<length;i++){
        PyObject* item = PySequence_Fast_GET_ITEM(pyList, i);
        if (PySequence_Size(item)!=2){
            printf("Error in %s: %s\n",__func__,"Malformed point format");
            return list;
        }
        float xValue;
        float yValue;
        if (PyArg_ParseTuple(item, "ff", &xValue, &yValue)) {
                list<<dpoint(xValue,yValue);
        } else {
            printf("Error in %s: %s\n",__func__,"Malformed number format");
            return list;
        }
    }
    return list;
}

PyObject* legacy_wrappers::stroke_parallel(PyObject *self, PyObject *args){
    ListBase<dpoint> list = legacy_wrappers::parse_list(self,args);
    if (list.size()>2){
        EditorSpirals editor = EditorSpirals();
        for (int i=0;i<list.size();i++){
            editor.addPoint(list.at(i));
        }
        try {
            editor.automatic();
        } catch (const char* text){
            printf("Error in %s: %s\n",__func__,text);
            PyObject* error;
            PyErr_SetString(error,text);
            return error;
        } catch (...){
            printf("Error in %s: %s\n",__func__," undefined");
            PyObject* error;
            PyErr_SetNone(error);
            return error;
        }

        ListCopyable<dpoint> result = ListCopyable<dpoint>();
        result = editor.getOutput();
        return legacy_wrappers::convert(result);
    }
}

PyObject* legacy_wrappers::stroke_sequential(PyObject *self, PyObject *args){
    ListBase<dpoint> list = legacy_wrappers::parse_list(self,args);
    if (list.size()>2){
        EditorCliffs editor = EditorCliffs();
        for (int i=0;i<list.size();i++){
            editor.addPoint(list.at(i));
        }
        try {
            editor.automatic();
        } catch (const char* text){
            printf("Error in %s: %s\n",__func__,text);
            PyObject* error;
            PyErr_SetString(error,text);
            return error;
        } catch (...){
            printf("Error in %s: %s\n",__func__," undefined");
            PyObject* error;
            PyErr_SetNone(error);
            return error;
        }

        ListCopyable<dpoint> result = ListCopyable<dpoint>();
        result = editor.getOutput();
        return legacy_wrappers::convert(result);
    }
}

PyMODINIT_FUNC initstopeight_clibs_legacy(void)
{
    (void) Py_InitModule("stopeight_clibs_legacy", stopeight_clibs_legacyMethods);
}
