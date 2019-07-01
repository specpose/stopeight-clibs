// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <stopeight-clibs/shared_types.h>
#include <stopeight-clibs/grapher.h>

#undef NDEBUG
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
PYBIND11_MAKE_OPAQUE(std::vector<double>);
PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);

using namespace pybind11;

PYBIND11_MODULE(grapher, m){
	object matrix_module = module::import("stopeight.matrix");

    class_<std::vector<double>>(m,"VectorDouble",buffer_protocol())
	.def(init<>())
	.def(init([](array_t<double,array::c_style> buffer){
		auto info = buffer.request();
		if (info.format != format_descriptor<double>::format())
			throw std::runtime_error("Incompatible format: Expected a double array format descriptor");
		if (info.itemsize != sizeof(double))
			throw std::runtime_error("Incompatible format: Expected double size items");
		if (info.ndim!= 1)
			throw std::runtime_error("Incompatible buffer dimensions");
		auto data = static_cast<double*>(info.ptr);
		auto vector = std::vector<double>(data,data+info.shape[0]);
		return vector;
	}))
	.def_buffer([](std::vector<double>& vector) -> buffer_info{
		return buffer_info(
			vector.data(),
			sizeof(double),
			format_descriptor<double>::format(),
			1,
			{size_t(vector.size())},
			{sizeof(double)}
		);
		})
	;
	m.def("create_vector_graph", [](array_t<double,array::c_style> buffer, int samplesPerVector, double unitaryLength, bool relative , double average, double averageScale)->array_t<sp::timecode<double>,array::c_style>{
		auto info = buffer.request();
		if (info.format != format_descriptor<double>::format())
			throw std::runtime_error("Incompatible format: Expected a double array format descriptor");
		if (info.itemsize != sizeof(double))
			throw std::runtime_error("Incompatible format: Expected double size items");
		if (info.ndim!= 1)
			throw std::runtime_error("Incompatible buffer dimensions");
		auto data = static_cast<double*>(info.ptr);
		auto vec = std::vector<double>(data,data+info.shape[0]);
		auto op = speczilla::Buffer<double>(&vec,vec.size(),samplesPerVector,unitaryLength,relative,average,averageScale);
		auto out = std::vector<sp::timecode<double>>{op()};//is sp::result, not std::vector<timecode>
		return cast(out);
    },arg("vector"),arg("samplesPerVector")=1,arg("unitaryLength")=1.0,arg("relative")=false,arg("average")=0.0,arg("averageScale")=1.0)
	;

	//basically the same as Vector, but not requiring matrix.h
    class_<std::vector<sp::timecode<double>>>(m,"VectorTimeCodeDouble",buffer_protocol())
	.def(init<>())
	.def(init([](array_t<sp::timecode<double>,array::c_style> buffer){
		auto info = buffer.request();
		// There is an existing bug in NumPy (as of v1.11): trailing bytes are
    	// not encoded explicitly into the format string. This will supposedly
		// get fixed in v1.12; for further details, see these:
		// - https://github.com/numpy/numpy/issues/7797
		// - https://github.com/numpy/numpy/pull/7798
		// Because of this, we won't use numpy's logic to generate buffer format
		// strings and will just do it ourselves.
		if (info.format != format_descriptor<sp::timecode<double>>::format()){
			throw std::runtime_error("Incompatible format: Expected a timecode array format descriptor");
			}
		if (info.itemsize != sizeof(sp::timecode<double>))
			throw std::runtime_error("Incompatible format: Expected timecode size items");
		if (info.ndim!= 1)
			throw std::runtime_error("Incompatible buffer dimensions");
		size_t size = info.shape[0];
		if (info.strides[0]!=sizeof(sp::timecode<double>))
		throw std::runtime_error("Incompatible format: Incompatible step size");
		auto data = static_cast<sp::timecode<double>*>(info.ptr);
		auto vector = std::vector<sp::timecode<double>>(data,data+size);
		return vector;
	}))
	.def_buffer([](std::vector<sp::timecode<double>>& vector) -> buffer_info{
		return buffer_info(
			vector.data(),
			sizeof(sp::timecode<double>),
			format_descriptor<sp::timecode<double>>::format(),
			1,
			{size_t(vector.size())},
			{sizeof(sp::timecode<double>)}
		);
		})
	.def("__array__",[](std::vector<sp::timecode<double>> &vec)->array_t<sp::timecode<double>,array::c_style>{return cast(vec);})
	;

//    class_<samples_To_VG<double>>(m,"Samples_To_VG")
//            .def(init<size_t,double,std::vector<size_t>>())//needs std::vector<size_t> type
////            .def("exec",overload_cast<fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&>(&samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle>))
////            .def("exec",overload_cast<fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&>(&samples_To_VG::operator()))
////            .def("exec",(void (samples_To_VG::*)(fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&)) &samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle> )
////            .def("exec",(void (samples_To_VG::*)(fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&)) &samples_To_VG::operator() )
//            .def("exec", &samples_To_VG<double>::operator()<angle::sharing_angle&>)//return type needs definition of sp::result!!!
//            ;

}
