// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "algo_impl.h"
//double define
#include <sycl/execution_policy>

// Taken from msvc symbol error; Shared between all explicit template instantiations
using fvect = sycl::helpers::BufferIterator<float, std::allocator<float> >;
using fexec = sycl::sycl_execution_policy<>;

grapher::__calculate_rotations::__calculate_rotations() {
}

grapher::__calculate_rotations::~__calculate_rotations() {
}

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__calculate_rotations::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	cl::sycl::queue sequential(task1.get_queue());
	//all kernels
	sycl::sycl_execution_policy<class transform1> task1_sub1_sub1(sequential);
	//sycl::impl::transform(task1_sub1, begin, end,begin2, [](float f) {return 3.3f; });//its doing queue stuff internally -> not sycl inside sycl
}
template void grapher::__calculate_rotations::operator()(fexec& task1, fvect begin, fvect end, fvect begin2);


grapher::samples_To_VG::samples_To_VG(int samplesPerPixel) : _samplesPerPixel(samplesPerPixel){
}

grapher::samples_To_VG::~samples_To_VG() {
}

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::samples_To_VG::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	cl::sycl::queue sequential(task1.get_queue());
	//all kernels
	sycl::sycl_execution_policy<class transform1> task1_sub1(sequential);
	//sycl::impl::transform(task1_sub1, begin, end,begin2, [](float f) {return 3.3f; });//its doing queue stuff internally -> not sycl inside sycl
	//buffer double single
	size_t size = std::distance(begin, end);
	cl::sycl::buffer<Iterator::value_type> b1 = sycl::helpers::make_temp_buffer<Iterator::value_type>(size);
	//__calculate_rotations
	//buffer double pair
	//__apply_rotation_matrix
	//buffer double pair (shorter!)
	//__add_scalars(samplesPerPixel)
}
template void grapher::samples_To_VG::operator()(fexec& task1, fvect begin, fvect end, fvect begin2);
//template void grapher::samples_To_VG(dvect begin, dvect end, dvect begin2);