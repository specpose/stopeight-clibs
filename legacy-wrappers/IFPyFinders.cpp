#include <Python.h>
#include "turns.h"
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
        f.def("findTurns",[](py::array_t<sp::timecode<double>,py::array::c_style> in)->std::vector<size_t>{
            //input
            auto data = (mod.attr("np_to_tc")(in)).cast<std::vector<sp::timecode<double>>>();
            auto data_qt = QList<dpoint>();
            //Hack Copy
            std::transform(std::begin(data),std::end(data),std::back_inserter(data_qt),[](sp::timecode<double>& it_in){
                return dpoint(qreal(it_in.coords[0]),qreal(it_in.coords[1]));
            });

            //return
            auto result_qt =  Turns<dpoint>::findTurns(data_qt);
            auto result = std::vector<size_t>();
            //gcc: auto or  windows: decltype
            std::transform(std::begin(result_qt),std::end(result_qt),std::back_inserter(result),[](dpoint& it_in){
                return size_t(it_in.position);
            });
            return result;
        });

}