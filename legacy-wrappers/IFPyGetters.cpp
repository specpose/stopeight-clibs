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
    py::class_<QListWrapper>(g,"QListDpoint", py::buffer_protocol())
	.def(py::init<py::array_t<sp::timecode<double>,py::array::c_style>>())
	.def("__len__",[](QListWrapper& in)->int{return in.size();})
	;
    py::class_<TurnAnalyzerWrapper>(g,"Turn", py::buffer_protocol())
	.def(py::init<QListWrapper&>())
    .def("next",[](TurnAnalyzerWrapper& in){
        //ListCopyable<dpoint> result_qt = in.getFirstTurnByTriplets();
		//QListWrapper result = QListWrapper(static_cast<QListWrapper>(result_qt));//Hack ListCopyable should not be cast
		QListWrapper result = in.getFirstTurnByTriplets();
		return result.toPyArray();
    })
	/*.def("__array__",[](TurnAnalyzerWrapper &in)->py::array_t<sp::timecode<double>,py::array::c_style>{
        QListWrapper result = QListWrapper(in);
        return result.toPyArray();
    })*/
	.def("__len__",[](TurnAnalyzerWrapper& in)->int{return in.size();})
	;
}
