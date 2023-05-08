#ifdef __VERSION__
#define VERSION __VERSION__
#elif
#define VERSION 0
#endif

#include "git.h"
#include <IFPyShared.h>
#undef NDEBUG
#include <pybind11/stl.h>
//dont remove opaque; custom caster return type std::vector<int> -> py_list
PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);

#include "spirals.h"
#include "cliffs.h"
#include "editorbase.h"
#include "analyzer.h"

std::vector<size_t> transform_indices(ListSwitchable<dpoint> result_qt){
    auto result = std::vector<size_t>();
    //gcc: auto or  windows: decltype
    std::transform(std::begin(result_qt),std::end(result_qt),std::back_inserter(result),[](dpoint& it_in){
        return size_t(it_in.position);
    });
    return result;
}

PYBIND11_MODULE(finders, f){
	f.attr("version") = VERSION;
	py::object getters_module = py::module::import("stopeight.getters");
    f.def("findSpiralCliffs",[](ListSwitchableWrapper& in)->std::vector<size_t>{
        return transform_indices(Spirals::findSpiralCliffs(in));
    });
    f.def("findCliffs",[](ListSwitchableWrapper& in)->std::vector<size_t>{
        return transform_indices(Cliffs::findCliffs(in));
    });
}
