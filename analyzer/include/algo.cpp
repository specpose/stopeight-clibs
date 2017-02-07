#include "algo.h"
#include <sycl/execution_policy>
#include "sycl/algorithm/for_each.hpp"

template <class Iterator>
void grapher::samples_To_VG(Iterator begin, Iterator end)
//void grapher::samples_To_VG(Iterator begin, Iterator end)
{
	//sycl::sycl_heterogeneous_execution_policy<class testname> pol;
	sycl::sycl_execution_policy<> independent;
	{//sync: buffer
		cl::sycl::default_selector h;
		//different queues?
		{//queue(s)
			cl::sycl::queue sequential(h);
			//all kernels
			sycl::sycl_execution_policy<class for_each1> task1(sequential);
			sycl::impl::for_each(task1, begin, end, [](float f) {return f = 3.3f; });
		}//kernels sync
	}//destruct: buffer
}

using veccy = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>>;

template void grapher::samples_To_VG(veccy begin, veccy end);