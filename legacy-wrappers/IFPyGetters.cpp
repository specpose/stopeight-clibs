#include <IFPyShared.h>
#undef NDEBUG
#include <pybind11/stl.h>
//cant remove opaque; no custom caster vector -> array?
PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);

PYBIND11_MODULE(getters, g){
    py::class_<QListWrapper>(g,"QListDpoint", py::buffer_protocol())
	.def(py::init<py::array_t<sp::timecode<double>,py::array::c_style>>())
	;
    py::class_<TurnAnalyzerWrapper>(g,"TurnAnalyzerDpoint", py::buffer_protocol())
	.def(py::init<QListWrapper&>())
    //.def("getFirstTurnByTriplets",&TurnAnalyzerWrapper::getFirstTurnByTriplets)
	;
    g.def("getFirstTurnByTriplets",[](py::array_t<sp::timecode<double>,py::array::c_style> in)->py::array_t<sp::timecode<double>,py::array::c_style>{
        //input
        QListWrapper data_qt = QListWrapper(in);
        //process
        auto analyzer = TurnAnalyzerWrapper(data_qt);
        ListCopyable<dpoint> result_qt = analyzer.getFirstTurnByTriplets();
        QListWrapper* result = static_cast<QListWrapper*>(&result_qt);
        return result->toPyArray();
    });

}