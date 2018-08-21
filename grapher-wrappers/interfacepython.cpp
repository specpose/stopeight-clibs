// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <pybind11/pybind11.h>
#include <stopeight-clibs/algo.h>
#include <stopeight-clibs/shared_types.h>
#include "dummy.h"
#include <stopeight-clibs/angle_functions.h>

//grapher
//#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
//PYBIND11_MAKE_OPAQUE(std::vector<int16_t>);
//PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<int16_t>>);
#include <stopeight-clibs/grapher.h>

//algo
#include <pybind11/stl.h>

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
	.def_readwrite("first",&sp::timecode<int16_t>::first)
	.def_readwrite("second",&sp::timecode<int16_t>::second);
    class_<sp::timecode<double>>(m,"TimeCodeDouble")
	.def(init<double,double>())
	.def_readwrite("first",&sp::timecode<double>::first)
	.def_readwrite("second",&sp::timecode<double>::second);
    m.def("VectorInt16",[](std::vector<int16_t> b){return std::vector<int16_t>{b};});
    m.def("VectorTCInt16",[](std::vector<sp::timecode<int16_t>> b){return std::vector<sp::timecode<int16_t>>{b};});
    m.def("VectorDouble",[](std::vector<int16_t> b){return std::vector<double>(b.begin(),b.end());});
    m.def("VectorTCDouble",[](std::vector<sp::timecode<int16_t>> b){return std::vector<sp::timecode<double>>(b.begin(),b.end());});
    //stl_bind //bind_vector<std::vector<int16_t>>(m,"VectorInt16",buffer_protocol());
    //bind_vector<std::vector<sp::timecode<int16_t>>>(m,"VectorTCInt16",buffer_protocol());
    //stl //m.def("create_vector_graph", [](std::vector<int16_t> vec)->std::vector<sp::timecode<int16_t>>{
    m.def("create_vector_graph", [](buffer in)->std::vector<sp::timecode<int16_t>>{
	buffer_info info = in.request();
	auto data = speczilla::Buffer<int16_t>(static_cast<std::vector<int16_t>*>(info.ptr));
	//auto data = speczilla::Buffer<int16_t>(&vec);
	auto out = data();
	/*auto out = std::vector<sp::timecode<int16_t>>();
	auto one = sp::timecode<int16_t>(12,15);
	auto two = sp::timecode<int16_t>(30,41);
	out.push_back(one);
	out.push_back(two);*/
	return out;
    },return_value_policy::move);

/*    class_<speczilla::Buffer<int16_t>>(m,"Buffer",buffer_protocol())
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

    class_<samples_To_VG>(m,"Samples_To_VG")
            .def(init<int,double,std::vector<int>>())
//            .def("exec",overload_cast<fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&>(&samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle>))
//            .def("exec",overload_cast<fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&>(&samples_To_VG::operator()))
//            .def("exec",(void (samples_To_VG::*)(fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&)) &samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle> )
//            .def("exec",(void (samples_To_VG::*)(fexec&, vector_single<double>,vector_single<double>,vector_pair<double>,angle::angle&)) &samples_To_VG::operator() )
            .def("exec", &samples_To_VG::operator()<fexec,vector_single<double>,vector_pair<double>,angle::angle> )
            ;
}
