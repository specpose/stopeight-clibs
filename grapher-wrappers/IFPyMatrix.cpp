// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <pybind11/pybind11.h>
#include <stopeight-clibs/Matrix.h>
#include <pybind11/numpy.h>

using namespace pybind11;

//new >2.2
PYBIND11_MODULE(matrix, m){
//old
//PYBIND11_PLUGIN(grapher){
//    pybind11::module m("matrix","");
//old

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
