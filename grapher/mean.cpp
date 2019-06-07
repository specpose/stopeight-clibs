// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "mean_impl.h"
#include "algo_impl.h"
#include "dummy.h"

namespace speczilla {
    
	template<typename T> Mean<T>::Mean(std::vector<T>* s)
    : PreloaderIF<T,double>( *this )
		, buf(s)
	{
	}
	template Mean<float>::Mean(std::vector<float>* s);
	template Mean<double>::Mean(std::vector<double>* s);

	template<typename T> Mean<T>::~Mean() {
	}
	template Mean<float>::~Mean();
	template Mean<double>::~Mean();

	template<typename T> double Mean<T>::operator()()
	{
		const int size = buf->size();
        //angle::averageScaled* afunc = nullptr;
		if (size > 0) {
			std::vector<T> differences = std::vector<T>(size, 0.0f);
			grapher::__differences(std::begin(*buf), std::end(*buf), std::begin(differences));
            auto a = angle::__average();
            return a(std::begin(differences)+1, std::end(differences));
		}
		else {
			return 0.0f;
		}
	}
	//specialization
	template double Mean<float>::operator()();
	template double Mean<double>::operator()();

}

//weird double defined symbol error for sycl::device from msvc
//#include "algo.cpp"
