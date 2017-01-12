// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "include/algo.h"

//double define
#include <sycl/execution_policy>
//#include <experimental/execution_policy>
//#include "sycl/algorithm/for_each.hpp"
#include <vector>

template <class Iterator>
void grapher::samples_To_VG(Iterator begin, Iterator end)
//void grapher::samples_To_VG(Iterator begin, Iterator end)
{
	//sycl::sycl_heterogeneous_execution_policy<class testname> pol;
	sycl::sycl_execution_policy<> independent;
	{//sync: buffer
		cl::sycl::default_selector h; //default sycl device
		//different queues?
		{//queue(s): it's a functor(handle)
			cl::sycl::queue sequential(h);
			//all kernels
			sycl::sycl_execution_policy<class for_each1> task1(sequential);
			sycl::impl::transform(task1, begin, end,begin, [](float f) {return 3.3f; });//its doing queue stuff internally -> not sycl inside sycl
		}//kernels sync
	}//destruct: buffer
}

// Taken from msvc symbol error
using fvect = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>>;
using dvect = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<double>>>;
template void grapher::samples_To_VG(fvect begin, fvect end);
template void grapher::samples_To_VG(dvect begin, dvect end);