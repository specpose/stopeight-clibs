#include <IFPyShared.h>
#undef NDEBUG
#include <pybind11/stl.h>
//cant remove opaque; no custom caster vector -> array?
PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);

#include "turns.h"

PYBIND11_MODULE(finders, f){
        //static QList<dpoint> findTurns(ListCopyable<dpoint> toBeProcessed);
        f.def("findTurns",[](py::array_t<sp::timecode<double>,py::array::c_style> in)->std::vector<size_t>{
            //input
            QList<dpoint> data_qt = QListWrapper(in);

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