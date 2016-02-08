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
        printf("Filename is not a list\n");
        return NULL;
    }
    ListBase<dpoint> myList = ListBase<dpoint>();
    try {
        myList= myList.open(pythonpath);
    } catch (const char* text){
        printf("Error in legacy file parser %s",text);
        PyObject* error;
        PyErr_SetString(error,text);
        return error;
    } catch (...){
        printf("Undefined error in legacy file parser");
        PyObject* error;
        PyErr_SetNone(error);
        return error;
    }

    printf("Loaded %d points from file %s\n",myList.size(),pythonpath);
    return legacy_wrappers::convert(myList);
}

ListBase<dpoint> legacy_wrappers::parse_list(PyObject *self, PyObject *args) {
    PyObject* obj;
    ListBase<dpoint> list = ListBase<dpoint>();
    if (!PyArg_ParseTuple(args, "O", &obj)){
        printf("Argument is supposed to be a list of a pair of numbers\n");
        return list;
    }
    PyObject* pyList = PySequence_Fast(obj,"Not a list");
    int length = PySequence_Size(obj);
    for (int i=0;i<length;i++){
        PyObject* item = PySequence_Fast_GET_ITEM(pyList, i);
        if (PySequence_Size(item)!=2){
            printf("Malformed point format\n");
            return list;
        }
        //PyObject* xObj = PySequence_Fast_GET_ITEM(item,0);
        //PyObject* yObj = PySequence_Fast_GET_ITEM(item,1);
        //PyObject* xRepr = PyObject_Repr(xObj);
        //PyObject* yRepr = PyObject_Repr(yObj);
        float xValue;
        float yValue;
        if (PyArg_ParseTuple(item, "ff", &xValue, &yValue)) {
            //if (PyFloat_Check(&xValue)&&PyFloat_Check(&yValue)){
            //    const double x = PyFloat_AS_DOUBLE(xObj);
            //    const double y = PyFloat_AS_DOUBLE(yObj);
                list<<dpoint(xValue,yValue);
            //}
        } else {
            printf("Malformed number format\n");
            return list;
        }
    }
    return list;
}

PyObject* legacy_wrappers::stroke_parallel(PyObject *self, PyObject *args){
    ListBase<dpoint> list = legacy_wrappers::parse_list(self,args);
    printf("Loaded %d points into Spiral Stroke Analyzer\n",list.size());
    if (list.size()>2){
        EditorSpirals editor = EditorSpirals();
        for (int i=0;i<list.size();i++){
            editor.addPoint(list.at(i));
        }
        try {
            editor.automatic();
        } catch (const char* text){
            printf("Error in parallel Stroke Analyzer: %s",text);
            PyObject* error;
            PyErr_SetString(error,text);
            return error;
        } catch (...){
            printf("Undefined error in parallel Stroke Analyzer");
            PyObject* error;
            PyErr_SetNone(error);
            return error;
        }

        ListCopyable<dpoint> result = ListCopyable<dpoint>();
        result = editor.getOutput();
        printf("Returned %d from Spiral Stroke Analyzer\n",result.size());
        return legacy_wrappers::convert(result);
    }
}

/*
  This is the sequential version of the stroke analyzer. It will subdivide pairs (cliffs) and triplets (turns) of immediately repeating features without further lookahead and center them.
*/
// Placeholder stroke_cliffs

PyMODINIT_FUNC initstopeight_clibs_legacy(void)
{
    (void) Py_InitModule("stopeight_clibs_legacy", stopeight_clibs_legacyMethods);
}
