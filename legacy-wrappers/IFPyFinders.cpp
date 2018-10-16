#include <Python.h>
//#include "turns.h"
#include <stopeight-clibs/shared_types.h>

#undef NDEBUG
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
//cant remove opaque; no custom caster vector -> array?
PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);
namespace py = pybind11;

auto mod = py::module::import("stopeight.grapher");

PYBIND11_MODULE(finders, f){
        //vec_tc(f,"VectorTimeCodeDouble",py::buffer_protocol());
        //static QList<dpoint> findTurns(ListCopyable<dpoint> toBeProcessed);
        f.def("findTurns",[](py::array_t<sp::timecode<double>,py::array::c_style> in)->std::vector<sp::timecode<double>>{
            return (mod.attr("np_to_tc")(in)).cast<std::vector<sp::timecode<double>>>();
        });

}