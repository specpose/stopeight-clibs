#include <IFPyShared.h>
#undef NDEBUG
#include <pybind11/stl.h>
//cant remove opaque; no custom caster vector -> array?
PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);

PYBIND11_MODULE(getters, g){
    py::class_<QListWrapper>(g,"QListDpoint", py::buffer_protocol())
	.def(py::init<py::array_t<sp::timecode<double>,py::array::c_style>>())
	;
    py::class_<TurnAnalyzerWrapper>(g,"Turn", py::buffer_protocol())
	.def(py::init<QListWrapper&>())
    .def("next",[](TurnAnalyzerWrapper& in){
        ListCopyable<dpoint> result_qt = in.getFirstTurnByTriplets();
        ListBase<dpoint>& result_ref = dynamic_cast<ListBase<dpoint>&>(result_qt);
        ListSwitchable<dpoint>& ref = static_cast<ListSwitchable<dpoint>&>(result_ref);
        QListWrapper& end = static_cast<QListWrapper&>(ref);
        return TurnAnalyzerWrapper(end);
    })
	.def("__array__",[](TurnAnalyzerWrapper &in)->py::array_t<sp::timecode<double>,py::array::c_style>{
        QListWrapper result = QListWrapper(in);
        return result.toPyArray();
    })
	;
}