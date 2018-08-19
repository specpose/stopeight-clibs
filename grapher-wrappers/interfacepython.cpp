// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <pybind11/pybind11.h>
#include <stopeight-clibs/algo.h>
#include <stopeight-clibs/shared_types.h>
#include "dummy.h"
#include <stopeight-clibs/angle_functions.h>

//grapher
#include <pybind11/stl_bind.h>
//#include <pybind11/numpy.h>
PYBIND11_MAKE_OPAQUE(std::vector<int16_t>);
#include <stopeight-clibs/grapher.h>

//algo
//#include <pybind11/stl.h>

using fexec = const dummy;

using namespace pybind11;
using namespace grapher;

//new >2.2
PYBIND11_MODULE(grapher, m){
//old
//PYBIND11_PLUGIN(grapher){
//    pybind11::module m("grapher","");
//old

    bind_vector<std::vector<int16_t>>(m,"VectorInt16",buffer_protocol());
    m.def("create_vector_graph", [](buffer vec)->buffer{
	buffer_info info = vec.request();
	auto data = speczilla::Buffer<int16_t>(static_cast<std::vector<int16_t>*>(info.ptr));
	return vec;
    });

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
