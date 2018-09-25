// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <pybind11/pybind11.h>
#include <stopeight-clibs/algo.h>
#include <stopeight-clibs/shared_types.h>
#include "dummy.h"
#include <stopeight-clibs/angle_functions.h>

#include <stopeight-clibs/grapher.h>

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

    class_<sp::timecode<int16_t>>(m,"TimeCodeInt",buffer_protocol())
	.def(init<int16_t,int16_t>())
	.def_buffer([](sp::timecode<int16_t>& tc) -> buffer_info{
	return buffer_info(
		tc.data(),
		sizeof(sp::timecode<int16_t>::value_type),
		format_descriptor<sp::timecode<int16_t>::value_type>::format(),
		1,
		{2},
		{sizeof(sp::timecode<int16_t>::value_type)}
	);
	})
	.def("get_x",&sp::timecode<int16_t>::get_x)
	.def("get_y",&sp::timecode<int16_t>::get_y)
	.def(self += self)
	;
    class_<sp::timecode<double>>(m,"TimeCodeDouble",buffer_protocol())
	.def(init<double,double>())
	.def_buffer([](sp::timecode<double>& tc) -> buffer_info{
	return buffer_info(
		tc.data(),
		sizeof(sp::timecode<double>::value_type),
		format_descriptor<sp::timecode<double>::value_type>::format(),
		1,
		{2},
		{sizeof(sp::timecode<double>::value_type)}
	);
	})
	.def("get_x",&sp::timecode<double>::get_x)
	.def("get_y",&sp::timecode<double>::get_y)
	.def(self += self)
	;
    class_<std::vector<sp::timecode<double>>>(m,"VectorTimeCodeDouble",buffer_protocol())
	.def(init<>())
	.def_buffer([](std::vector<sp::timecode<double>>& vector) -> buffer_info{
		return buffer_info(
			vector.data(),
			sizeof(std::vector<sp::timecode<double>>::value_type),
			"",//format_descriptor<sp::timecode<double>>::format(),
			1,
			{size_t(vector.size())},
			{sizeof(sp::timecode<double>)}
		);
		})
	.def("np",[](std::vector<sp::timecode<double>> &vec)->array{return cast(vec);})
	;
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

    m.def("tcraw",[]()->size_t{return sizeof(std::array<double,2>);});
    m.def("tcobject",[]()->size_t{return sizeof(sp::timecode<double>);});
}
