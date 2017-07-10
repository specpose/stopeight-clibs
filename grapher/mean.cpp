// Copyright (C) 2009-2016 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "mean_impl.h"
#include "algo_impl.h"
#include "dummy.h"

namespace grapher {

	template<typename T> grapher::Mean<T>::Mean() {
	}

	template<typename T> grapher::Mean<T>::Mean(std::vector<T>* s)
		: PreloaderIF( *this )
		, buf(s)
	{
	}
	template grapher::Mean<float>::Mean(std::vector<float>* s);
	template grapher::Mean<double>::Mean(std::vector<double>* s);

	template<typename T> grapher::Mean<T>::~Mean() {
	}
	template grapher::Mean<float>::~Mean();
	template grapher::Mean<double>::~Mean();

	template<typename T> double Mean<T>::operator()()
	{
		const int size = buf->size();
		grapher::averageScaled* afunc = nullptr;
		if (size > 0) {
			std::vector<double> differences = std::vector<double>(size, 0.0f);
			grapher::__differences()(dummy_policy, std::begin(*buf), std::end(*buf), std::begin(differences));
			return grapher::__average()(std::begin(differences)+1, std::end(differences));
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