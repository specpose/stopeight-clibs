// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <stopeight-clibs/algo.h>
#include <stopeight-clibs/shared_types.h>
#include <stopeight-clibs/angle_functions.h>
#include <stopeight-clibs/grapher.h>
#include "dummy.h"
using fexec = const dummy;
using namespace grapher;

#undef NDEBUG
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
//cant make this opaque; have to use stl or manual move: cast py::array to std::vector
//PYBIND11_MAKE_OPAQUE(std::vector<double>);
//cant remove opaque; no custom caster vector -> array?
PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);
using namespace pybind11;

//template<typename T> class tc {public: tc(){};tc(T x,T y){};
//~tc(){};
//tc& operator=(tc<T> other){};
//tc& operator+=(const tc<T>& b){};
//std::array<T,2> coords; sp::FixpointType type;};

//new >2.2
PYBIND11_MODULE(grapher, m){
//old
//PYBIND11_PLUGIN(grapher){
//    pybind11::module m("grapher","");
//old
    /*class_<std::vector<double>>(m,"VectorDouble",buffer_protocol())
	.def(init<>())
	.def_buffer([](std::vector<double>& vector) -> buffer_info{
		return buffer_info(
			vector.data(),
			sizeof(double),
			//"T{(2)d:coords:i:type:}",
			format_descriptor<double>::format(),
			1,
			{size_t(vector.size())},
			{sizeof(double)}
		);
		})
	.def("__array__",[](std::vector<double> &vec)->array{return cast(vec);})
	;*/
    PYBIND11_NUMPY_DTYPE(sp::timecode<double>, coords, type, tct_type, cov_type);
    class_<std::vector<sp::timecode<double>>>(m,"VectorTimeCodeDouble",buffer_protocol())
	.def(init<>())
	.def_buffer([](std::vector<sp::timecode<double>>& vector) -> buffer_info{
		return buffer_info(
			vector.data(),
			sizeof(sp::timecode<double>),
			//"T{(2)d:coords:i:type:}",
			format_descriptor<sp::timecode<double>>::format(),
			1,
			{size_t(vector.size())},
			{sizeof(sp::timecode<double>)}
		);
		})
	.def("__array__",[](std::vector<sp::timecode<double>> &vec)->array{return cast(vec);})
	;
//    PYBIND11_NUMPY_DTYPE(tc<double>, coords, type);
//    bind_vector<std::vector<tc<double>>>(m,"VectorTimeCodeDouble", buffer_protocol());

    m.def("np_to_tc",[](array_t<sp::timecode<double>,array::c_style> in)->std::vector<sp::timecode<double>>{
	buffer_info info = in.request();
	if (info.format != "T{(2)d:coords:i:type:}"){
		//std::cout<<"\n"<<format_descriptor<sp::timecode<double>>::format()<<"\n";
                //std::cout<<info.format<<"\n";
		throw std::runtime_error("Incompatible format: Expected a timecode array format descriptor");
        }
	if (info.itemsize != sizeof(sp::timecode<double>))
		throw std::runtime_error("Incompatible format: Expected timecode size items");
	if (info.ndim!= 1)
		throw std::runtime_error("Incompatible buffer dimensions");
	size_t size = info.shape[0];
	if (info.strides[0]!=sizeof(sp::timecode<double>))
		throw std::runtime_error("Incompatible format: Incompatible step size");
	auto timecodes=static_cast<sp::timecode<double>*>(info.ptr);
	auto vec = std::vector<sp::timecode<double>>(timecodes,timecodes+size);
	//needs stl.h (copy?)
	//vec = in.cast<std::vector<sp::timecode<double>>>();
	return vec;
	});

    m.def("create_vector_graph", [](array_t<double,array::c_style> in, int samplesPerVector, double unitaryLength, bool relative , double average, double averageScale)->array_t<sp::timecode<double>,array::c_style>{
	buffer_info info = in.request();
	if (info.format != format_descriptor<double>::format())
		throw std::runtime_error("Incompatible format: Expected a double array format descriptor");
	if (info.itemsize != sizeof(double))
		throw std::runtime_error("Incompatible format: Expected double size items");
	if (info.ndim!= 1)
		throw std::runtime_error("Incompatible buffer dimensions");
	size_t size = info.shape[0];
	if (info.strides[0]!=sizeof(double))
		throw std::runtime_error("Incompatible format: Incompatible step size");
	//auto doubles=static_cast<double*>(info.ptr);
	//auto vec = std::vector<double>(doubles,doubles+size);
	//needs stl.h (copy?)
	auto vec = in.cast<std::vector<double>>();
	auto data = speczilla::Buffer<double>(&vec,vec.size(),samplesPerVector,unitaryLength,relative,average,averageScale);
	auto out = data();
	return cast(out);
    },arg("vector"),arg("samplesPerVector")=1,arg("unitaryLength")=1.0,arg("relative")=false,arg("average")=0.0,arg("averageScale")=1.0, return_value_policy::move);

//    class_<samples_To_VG<double>>(m,"Samples_To_VG")
//            .def(init<size_t,double,std::vector<size_t>>())//needs std::vector<size_t> type
////            .def("exec",overload_cast<fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&>(&samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle>))
////            .def("exec",overload_cast<fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&>(&samples_To_VG::operator()))
////            .def("exec",(void (samples_To_VG::*)(fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&)) &samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle> )
////            .def("exec",(void (samples_To_VG::*)(fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&)) &samples_To_VG::operator() )
//            .def("exec", &samples_To_VG<double>::operator()<angle::sharing_angle&>)//return type needs definition of sp::result!!!
//            ;

}
