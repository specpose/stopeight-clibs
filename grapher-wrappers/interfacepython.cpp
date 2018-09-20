// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <pybind11/pybind11.h>
#include <stopeight-clibs/algo.h>
#include <stopeight-clibs/shared_types.h>
#include "dummy.h"
#include <stopeight-clibs/angle_functions.h>

#include <stopeight-clibs/grapher.h>
#include <stopeight-clibs/Matrix.h>

#include <pybind11/stl.h>
#include <pybind11/operators.h>
//#include <pybind11/stl_bind.h>
//PYBIND11_MAKE_OPAQUE(std::vector<double>);
//PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);
#include <pybind11/numpy.h>

using fexec = const dummy;

using namespace pybind11;
using namespace grapher;

//new >2.2
PYBIND11_MODULE(grapher, m){
//old
//PYBIND11_PLUGIN(grapher){
//    pybind11::module m("grapher","");
//old

    class_<sp::timecode<int16_t>>(m,"TimeCodeInt")
	.def(init<int16_t,int16_t>())
	.def("get_x",&sp::timecode<int16_t>::get_x)
        .def("get_y",&sp::timecode<int16_t>::get_y)
	.def(self += self);
    class_<sp::timecode<double>>(m,"TimeCodeDouble")
	.def(init<double,double>())
	.def("get_x",&sp::timecode<double>::get_x)
	.def("get_y",&sp::timecode<double>::get_y)
	.def(self += self);
    /*stl
    m.def("VectorInt16",[](std::vector<int16_t> b){return std::vector<int16_t>{b};});
    m.def("VectorTCInt16",[](std::vector<sp::timecode<int16_t>> b){return std::vector<sp::timecode<int16_t>>{b};});
    m.def("VectorDouble",[](std::vector<int16_t> b){return std::vector<double>(b.begin(),b.end());});
    m.def("VectorTCDouble",[](std::vector<sp::timecode<int16_t>> b){return std::vector<sp::timecode<double>>(b.begin(),b.end());});*/
    /*stl_bind
    bind_vector<std::vector<double>>(m,"VectorDouble",buffer_protocol());
    bind_vector<std::vector<sp::timecode<double>>>(m,"VectorTCDouble",buffer_protocol());*/
    /*speczilla::Buffer has private buf member
    class_<speczilla::Buffer<int16_t>>(m,"Buffer",buffer_protocol())
        .def_buffer([](speczilla::Buffer<int16_t> &b) -> buffer_info{
                return buffer_info{
                    b.buf,
                    sizeof(int16_t),
                    format_descriptor<int16_t>::format(),
                    1,
                    { b.buf.size() },
                    { sizeof(int16_t) }
                };

    });*/

    m.def("create_vector_graph", [](std::vector<double> in, int samplesPerVector, double unitaryLength, bool relative , double average, double averageScale)->std::vector<sp::timecode<double>>{
	auto data = speczilla::Buffer<double>(&in,in.size(),samplesPerVector,unitaryLength,relative,average,averageScale);	
	auto out = data();
	return out;
    },arg("vector"),arg("samplesPerVector")=1,arg("unitaryLength")=1.0,arg("relative")=false,arg("average")=0.0,arg("averageScale")=1.0, return_value_policy::move);

    class_<samples_To_VG>(m,"Samples_To_VG")
            .def(init<int,double,std::vector<int>>())
//            .def("exec",overload_cast<fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&>(&samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle>))
//            .def("exec",overload_cast<fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&>(&samples_To_VG::operator()))
//            .def("exec",(void (samples_To_VG::*)(fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&)) &samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle> )
//            .def("exec",(void (samples_To_VG::*)(fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&)) &samples_To_VG::operator() )
            .def("exec", &samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle> )
            ;

    class_<Matrix<double>>(m,"Matrix",buffer_protocol())
	.def(init<double,double,double,double,double,double,double,double,double>())
	.def_buffer([](Matrix<double>& matrix) -> buffer_info{
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
	/*.def("__init__",[](Matrix<double>& matrix, buffer buffer){
		buffer_info info = buffer.request();
		new (&matrix) Matrix();
	})*/
	;
    class_<Vector<double>>(m,"Vector",buffer_protocol())
	.def(init<double,double>())
	.def_buffer([](Vector<double>& vector) -> buffer_info{
	return buffer_info(
		vector.data(),
		sizeof(Vector<double>::value_type),
		format_descriptor<Vector<double>::value_type>::format(),
		1,
		{3},
		{sizeof(Vector<double>::value_type)}
	);
	})
	;
    //PYBIND11_NUMPY_DTYPE(Vector);
    class_<Vectors<double>>(m,"Vectors",buffer_protocol())
	.def(init<>())
	.def_buffer([](Vectors<double>& vectors) -> buffer_info{
	return buffer_info(
		vectors.data(),
		sizeof(Vectors<double>::value_type),
		format_descriptor<std::array<double,3>>::format(),
		1,
		{size_t(vectors.size())},
		{sizeof(double)*3}
	);
	})
	.def("push_back",&Vectors<double>::push_back)
	.def("apply",&Vectors<double>::apply)
	.def("np",[](Vectors<double> &vec)->array{return cast(vec);})
	;
    m.def("doublesize",[]()->size_t{return sizeof(std::array<double,9>);});
    m.def("matrixsize",[]()->size_t{return sizeof(Matrix<double>);});
    m.def("arraysize",[]()->size_t{return sizeof(std::array<double,9>);});
    class_<Stack<double>>(m,"Stack",buffer_protocol())
	.def(init<>())
	.def_buffer([](Stack<double>& stack) -> buffer_info{
	return buffer_info(
		stack.data(),
		sizeof(Stack<double>::value_type),
		"",//format_descriptor<Stack<double>::value_type>::format(),
		1,
		{stack.size()},
		{sizeof(Stack<double>::value_type)}
	);
	})
	.def("identity",&Stack<double>::identity)
	.def("scale",&Stack<double>::scale<double>)
	.def("rotate",&Stack<double>::rotate)
	.def("translate",&Stack<double>::translate<double>)
	;
}
