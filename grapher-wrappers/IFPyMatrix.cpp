// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1
#include <stopeight-clibs/Matrix.h>
#include <stopeight-clibs/shared_types.h>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

using namespace pybind11;

//new >2.2
PYBIND11_MODULE(matrix, m){
//old
//PYBIND11_PLUGIN(grapher){
//    pybind11::module m("matrix","");
//old
//    PYBIND11_NUMPY_DTYPE(Vector<double>, coords);
    PYBIND11_NUMPY_DTYPE(sp::timecode<double>, coords, type, tct_type, cov_type);

    class_<Matrix<sp::timecode<double>>>(m,"Matrix",buffer_protocol())
	.def(init<double,double,double,double,double,double,double,double,double>())
	.def_buffer([](Matrix<sp::timecode<double>>& matrix) -> buffer_info{
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
	.def("__array__",[](Matrix<sp::timecode<double>> &mat)->array{return cast(mat);})
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
    class_<Vectors<sp::timecode<double>>>(m,"Vectors",buffer_protocol())
	.def(init<>())
	.def_buffer([](Vectors<sp::timecode<double>>& vectors) -> buffer_info{
	return buffer_info(
		vectors.data(),
		sizeof(sp::timecode<double>),
//		format_descriptor<std::array<double,3>>::format(),
		format_descriptor<sp::timecode<double>>::format(),
		1,
		{size_t(vectors.size())},
		{sizeof(sp::timecode<double>)}
	);
	})
//todo
//	.def("push_back",&Vectors<sp::timecode<double>>::push_back)
	.def("apply",&Vectors<sp::timecode<double>>::apply)
	.def("__array__",[](Vectors<sp::timecode<double>> &vecs)->array{return cast(vecs);})
	;
    m.def("matrixsize",[](){return sizeof(Matrix<sp::timecode<double>>);});
    m.def("array",[](){return sizeof(std::array<double,9>);});
    class_<Stack<sp::timecode<double>>>(m,"Stack",buffer_protocol())
	.def(init<>())
	.def_buffer([](Stack<sp::timecode<double>>& stack) -> buffer_info{
	return buffer_info(
		stack.data(),
		sizeof(Stack<sp::timecode<double>>::value_type),
		format_descriptor<std::array<double,9>>::format(),
		1,
		{stack.size()},
		{sizeof(Stack<sp::timecode<double>>::value_type)}
	);
	})
	.def("identity",&Stack<sp::timecode<double>>::identity)
	.def("scale",&Stack<sp::timecode<double>>::scale<double>)
	.def("rotate",&Stack<sp::timecode<double>>::rotate<double>)
	.def("translate",&Stack<sp::timecode<double>>::translate<double>)
	.def("__array__",[](Stack<sp::timecode<double>> &stk)->array{return cast(stk);})
	;
}
