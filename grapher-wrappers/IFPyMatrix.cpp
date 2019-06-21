// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <stopeight-clibs/Matrix.h>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

using namespace pybind11;

//new >2.2
PYBIND11_MODULE(matrix, m){
//old
//PYBIND11_PLUGIN(grapher){
//    pybind11::module m("matrix","");
//old
    PYBIND11_NUMPY_DTYPE(Vector<double>, coords);

    class_<Matrix<Vector<double>>>(m,"Matrix",buffer_protocol())
	.def(init<double,double,double,double,double,double,double,double,double>())
	.def_buffer([](Matrix<Vector<double>>& matrix) -> buffer_info{
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
	.def("__array__",[](Matrix<Vector<double>> &mat)->array{return cast(mat);})
	;
//    class_<Vector<double>>(m,"Vector",buffer_protocol())
//	.def(init<double,double>())
//	.def_buffer([](Vector<double>& vector) -> buffer_info{
//	return buffer_info(
//		vector.data(),
//		sizeof(Vector<double>::value_type),
//		format_descriptor<Vector<double>::value_type>::format(),
//		1,
//		{3},
//		{sizeof(Vector<double>::value_type)}
//	);
//	})
//	.def("__array__",[](Vector<double> &vec)->array{return cast(vec);})
//	;
    class_<Vectors<Vector<double>>>(m,"Vectors",buffer_protocol())
	.def(init<>())
	.def_buffer([](Vectors<Vector<double>>& vectors) -> buffer_info{
	return buffer_info(
		vectors.data(),
		sizeof(Vector<double>),
//		format_descriptor<std::array<double,3>>::format(),
		format_descriptor<Vector<double>>::format(),
		1,
		{size_t(vectors.size())},
		{sizeof(Vector<double>)}
	);
	})
//todo
//	.def("push_back",&Vectors<Vector<double>>::push_back)
	.def("apply",&Vectors<Vector<double>>::apply)
	.def("__array__",[](Vectors<Vector<double>> &vecs)->array{return cast(vecs);})
	;
    m.def("matrixsize",[](){return sizeof(Matrix<Vector<double>>);});
    m.def("array",[](){return sizeof(std::array<double,9>);});
    class_<Stack<Vector<double>>>(m,"Stack",buffer_protocol())
	.def(init<>())
	.def_buffer([](Stack<Vector<double>>& stack) -> buffer_info{
	return buffer_info(
		stack.data(),
		sizeof(Stack<Vector<double>>::value_type),
		format_descriptor<std::array<double,9>>::format(),
		1,
		{stack.size()},
		{sizeof(Stack<Vector<double>>::value_type)}
	);
	})
//	.def("identity",&Stack<Vector<double>>::identity)
//	.def("scale",&Stack<Vector<double>>::scale<double>)
	.def("rotate",&Stack<Vector<double>>::rotate<double>)
	.def("translate",&Stack<Vector<double>>::translate<double>)
	.def("__array__",[](Stack<Vector<double>> &stk)->array{return cast(stk);})
	;
}
