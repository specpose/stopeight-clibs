// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#undef NDEBUG

#include <pybind11/pybind11.h>
#include <stopeight-clibs/algo.h>
#include <stopeight-clibs/shared_types.h>
#include "dummy.h"
#include <stopeight-clibs/angle_functions.h>

#include <stopeight-clibs/grapher.h>

//#include <pybind11/stl.h>
#include <pybind11/operators.h>
//#include <pybind11/stl_bind.h>
//cant make this opaque; have to use stl or manual move: cast py::array to std::vector
//PYBIND11_MAKE_OPAQUE(std::vector<double>);
//PYBIND11_MAKE_OPAQUE(std::vector<sp::timecode<double>>);
#include <pybind11/numpy.h>

using fexec = const dummy;

using namespace pybind11;
using namespace grapher;
#include <iostream>

//template<typename T> class tc {public: tc(){};tc(T x,T y){};
//~tc(){};
//tc& operator=(tc<T> other){};
//tc& operator+=(const tc<T>& b){};
//std::array<T,2> coords; sp::FixpointType type;};
    class CompleteBogus {
	public:
//		CompleteBogus(){std::cout<<"defcon";}
//		CompleteBogus(const CompleteBogus& other){std::cout<<"copycon";}
//		CompleteBogus(CompleteBogus&& other){std::cout<<"movecon";}
		CompleteBogus(buffer other){std::cout<<"buffercon";}
    };
#include <iostream>

//new >2.2
PYBIND11_MODULE(grapher, m){
//old
//PYBIND11_PLUGIN(grapher){
//    pybind11::module m("grapher","");
//old

    /*class_<sp::timecode<int16_t>>(m,"TimeCodeInt",buffer_protocol())
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
	;*/
    PYBIND11_NUMPY_DTYPE(sp::timecode<double>, coords, type);
    /*class_<sp::timecode<double>>(m,"TimeCodeDouble",buffer_protocol())
	.def(init<double,double>())
	.def_buffer([](sp::timecode<double>& tc) -> buffer_info{
	return buffer_info(
		&tc,
		sizeof(sp::timecode<double>),
		format_descriptor<sp::timecode<double>>::format(),
		1,
		{1},
		{sizeof(sp::timecode<double>)}
	);
	})
	.def(self += self)
	;*/
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

    class_<CompleteBogus>(m,"CompleteBogus", buffer_protocol())
//    .def(init<>())
//    .def(init<CompleteBogus&>())
//    .def(init<CompleteBogus&&>())
    .def(init<buffer>())
    //.def(init([](array_t<double,array::c_style>& pybogus){return CompleteBogus();}))
    .def("np",[](CompleteBogus& vec)->array{return cast(vec);})
    ;
//    PYBIND11_NUMPY_DTYPE(tc<double>, coords, type);
//    bind_vector<std::vector<tc<double>>>(m,"VectorTimeCodeDouble", buffer_protocol());
//    PYBIND11_NUMPY_DTYPE(sp::timecode<double>, coords, type);
//    bind_vector<std::vector<sp::timecode<double>>>(m,"VectorTimeCodeDouble", buffer_protocol());
//    bind_vector<std::vector<double>>(m,"VectorDouble", buffer_protocol());



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
	std::vector<sp::timecode<double>> vec = std::vector<sp::timecode<double>>(size);
	//auto timecodes=static_cast<sp::timecode<double>*>(info.ptr);
	//vec.assign(timecodes,timecodes+size);
	vec = in.cast<std::vector<sp::timecode<double>>>();
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
	auto doubles=static_cast<double*>(info.ptr);
	std::vector<double> vec = std::vector<double>(size);
	vec.assign(doubles,doubles+size);
	//needs stl.h (copy?)
	//vec = in.cast<std::vector<double>>();
	auto data = speczilla::Buffer<double>(&vec,vec.size(),samplesPerVector,unitaryLength,relative,average,averageScale);
	//auto data = speczilla::Buffer<double>(&in,in.size(),samplesPerVector,unitaryLength,relative,average,averageScale);	
	auto out = data();
	//std::cout<<out.size();
	return cast(out);
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
