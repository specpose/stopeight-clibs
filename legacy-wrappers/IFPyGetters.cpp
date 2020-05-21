#include "git.h"
#include <IFPyShared.h>
#undef NDEBUG
#include <pybind11/stl.h>
//cant remove opaque; no custom caster vector -> array?
PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);

PYBIND11_MODULE(getters, g){
	if(GitMetadata::Populated()) {
		py::object sha;
	        if(GitMetadata::AnyUncommittedChanges()) {
			sha = py::cast(GitMetadata::CommitSHA1()+"+dirty");
	        } else {
			sha = py::cast(GitMetadata::CommitSHA1());
		}
		g.attr("version") = sha;
	}
    py::class_<ListCopyableWrapper>(g,"ListCopyable", py::buffer_protocol())
	.def(py::init<py::array_t<sp::timecode<double>,py::array::c_style>>())
	.def("__len__",[](ListCopyableWrapper& in)->int{return in.size();})
	;
    py::class_<TurnAnalyzerWrapper>(g,"Turn", py::buffer_protocol())
	.def(py::init<ListCopyableWrapper&>())
    .def("next",[](TurnAnalyzerWrapper& in){
		in.rotateSegmentToXAxis();
        ListCopyableWrapper result = in.getFirstTurnByTriplets();
		return result.toPyArray();
    })
	/*.def("__array__",[](TurnAnalyzerWrapper &in)->py::array_t<sp::timecode<double>,py::array::c_style>{
        ListCopyableWrapper result = ListCopyableWrapper(in);
        return result.toPyArray();
    })*/
	.def("__len__",[](TurnAnalyzerWrapper& in)->int{return in.size();})
	;
	py::class_<ListSwitchableWrapper>(g,"ListSwitchable", py::buffer_protocol())
	.def(py::init<py::array_t<sp::timecode<double>,py::array::c_style>>())
	.def("__len__",[](ListSwitchableWrapper& in)->int{return in.size();})
	;
	/*py::class_<ListSwitchable<dpoint>>(g,"Corner", py::buffer_protocol())
	.def(py::init<ListSwitchableWrapper&>())
    .def("next",[](ListSwitchable<dpoint>& in){
		in.rotateSegmentToXAxis();
		ListSwitchableWrapper result = CornerAnalyzer::getFirstCorner(in);//Uses LSW move constructor
		return result.toPyArray();
    })
	.def("__len__",[](ListSwitchable<dpoint>& in)->int{return in.size();})
	;*/
	g.def("getFirstCorner",[](ListSwitchableWrapper& in){
		in.rotateSegmentToXAxis();
		ListSwitchableWrapper result = CornerAnalyzer::getFirstCorner(in);//Uses LSW move constructor
		return result.toPyArray();
	});
}
