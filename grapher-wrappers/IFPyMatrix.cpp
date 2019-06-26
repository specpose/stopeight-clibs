// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <stopeight-clibs/Matrix.h>
#include <stopeight-clibs/shared_types.h>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#undef NDEBUG
#define DEBUG
#include <iostream>

//#include <pybind11/stl_bind.h>
PYBIND11_MAKE_OPAQUE(Vectors<std::vector<sp::timecode<double>>>);

using namespace pybind11;

//new >2.2
PYBIND11_MODULE(matrix, m){
//old
//PYBIND11_PLUGIN(grapher){
//    pybind11::module m("matrix","");
//old

//    PYBIND11_NUMPY_DTYPE(Vector<double>, coords);
	enum_<sp::FixpointType>(m,"FixpointType",module_local(false))
		.value("EMPTY",sp::FixpointType::EMPTY)
		.value("FIXPOINT",sp::FixpointType::FIXPOINT);
	enum_<sp::tctype>(m,"tctype",module_local(false))
		.value("EMPTY",sp::tctype::EMPTY)
		.value("SWING",sp::tctype::SWING)
		.value("CREST",sp::tctype::CREST)
		.value("DUNE",sp::tctype::DUNE)
		.value("EDGE",sp::tctype::EDGE)
		.value("LEGALSEGMENT",sp::tctype::LEGALSEGMENT)
		.value("CLIFF",sp::tctype::CLIFF)
		.value("SPIRAL",sp::tctype::SPIRAL)
		//Corner??
		.value("STRAIGHT",sp::tctype::STRAIGHT);
	enum_<sp::covertype>(m,"covertype",module_local(false))
		.value("EMPTY",sp::covertype::EMPTY)
		.value("SWELL",sp::covertype::SWELL)
		.value("SPIRAL",sp::covertype::SPIRAL)
		.value("ZIGZAG",sp::covertype::ZIGZAG);
    PYBIND11_NUMPY_DTYPE(sp::timecode<double>, coords, type, tct_type, cov_type);
	class_<sp::timecode<double>> time_code(m,"TimeCode");
	time_code.def(init([](double x, double y){
		sp::timecode<double> tc{};
		return tc.__init({x,y});
	}))
	.def_readwrite("type", &sp::timecode<double>::type)
	.def_readwrite("tct_type", &sp::timecode<double>::tct_type)
	.def_readwrite("cov_type", &sp::timecode<double>::cov_type);

    class_<Matrix<std::vector<sp::timecode<double>>>>(m,"Matrix",buffer_protocol())
	.def(init<double,double,double,double,double,double,double,double,double>())
	.def_buffer([](Matrix<std::vector<sp::timecode<double>>>& matrix) -> buffer_info{
	return buffer_info(
		matrix.data(),
		sizeof(double),
		format_descriptor<double>::format(),
		2,
		{3,3},//rows, cols
		{ sizeof(double) * 3,//rows
		sizeof(double) }
	);
    	})
	.def("__array__",[](Matrix<std::vector<sp::timecode<double>>> &mat)->array{return cast(mat);})
	;
	
//this enables append, insert, etc. but overwrites init constructors below
//	bind_vector<Vectors<std::vector<sp::timecode<double>>>>(m,"Vectors", buffer_protocol())
    class_<Vectors<std::vector<sp::timecode<double>>>>(m,"Vectors",buffer_protocol())
	.def(init<>())
 	.def(init([](array_t<sp::timecode<double>,array::c_style> buffer){
		auto info = buffer.request();
		auto data = static_cast<sp::timecode<double>*>(info.ptr);
		auto vector = Vectors<std::vector<sp::timecode<double>>>(data,data+info.shape[0]);
		std::cout<<vector.data();
		return vector;
	}))
 	.def_buffer([](Vectors<std::vector<sp::timecode<double>>>& vectors) -> buffer_info{
	return buffer_info(
		vectors.data(),
		sizeof(sp::timecode<double>),
		format_descriptor<sp::timecode<double>>::format(),
		1,
		{size_t(vectors.size())},
		{sizeof(sp::timecode<double>)}
	);
	}) 
//todo
//	.def("push_back",&Vectors<std::vector<sp::timecode<double>>>::push_back)
	.def("apply",&Vectors<std::vector<sp::timecode<double>>>::apply)
	.def("__array__",[](Vectors<std::vector<sp::timecode<double>>> &vecs)->array{return cast(vecs);})
	;
//	m.def("dtype",[](){return format_descriptor<std::declval<Vectors<std::vector<sp::timecode<double>>>>()>::format();});
//	m.def("dtype",[](){return std::declval<array>().dtype;});
//	m.def("dtype",[](){return dtype(format_descriptor<sp::timecode<double>>::format());});
	m.def("ptr_v",[](Vectors<std::vector<sp::timecode<double>>> &vecs){
		std::cout<<vecs.data();
	});
	m.def("ptr_n",[](array_t<sp::timecode<double>,array::c_style> buffer){
		auto info = buffer.request();
		std::cout<<info.ptr;
	});
	m.def("to_tc",[](array_t<sp::timecode<double>,array::c_style> buffer)->Vectors<std::vector<sp::timecode<double>>>{
//	m.def("to_tc",[](array_t<sp::timecode<double>,array::c_style> buffer){
//		auto info = buffer.request();
//		auto data = static_cast<sp::timecode<double>*>(info.ptr);
//		auto vector = Vectors<std::vector<sp::timecode<double>>>(data,data+info.shape[0]);
//		std::cout<<vector.data();
//		return vector;
		return buffer.cast<Vectors<std::vector<sp::timecode<double>>>>();
	});
    m.def("matrixsize",[](){return sizeof(Matrix<std::vector<sp::timecode<double>>>);});
    m.def("array",[](){return sizeof(std::array<double,9>);});
    class_<Stack<std::vector<sp::timecode<double>>>>(m,"Stack",buffer_protocol())
	.def(init<>())
	.def_buffer([](Stack<std::vector<sp::timecode<double>>>& stack) -> buffer_info{
	return buffer_info(
		stack.data(),
		sizeof(Stack<std::vector<sp::timecode<double>>>::value_type),
		format_descriptor<std::array<double,9>>::format(),
		1,
		{stack.size()},
		{sizeof(Stack<std::vector<sp::timecode<double>>>::value_type)}
	);
	})
	.def("identity",&Stack<std::vector<sp::timecode<double>>>::identity)
	.def("scale",&Stack<std::vector<sp::timecode<double>>>::scale<double>)
	.def("rotate",&Stack<std::vector<sp::timecode<double>>>::rotate<double>)
	.def("translate",&Stack<std::vector<sp::timecode<double>>>::translate<double>)
	.def("__array__",[](Stack<std::vector<sp::timecode<double>>> &stk)->array{return cast(stk);})
	;
}
