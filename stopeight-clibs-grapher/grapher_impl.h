// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once

#include <vector>

#include "shared_types.h"

#include "preloaderif.h"

namespace grapher {

	template<typename T>class Buffer : public PreloaderIF<T, sp::result>
	{
	public:
		Buffer<T>();
		Buffer<T>(std::vector<T>* s);
		explicit Buffer<T>(std::vector<T>* s, int showSamples, int samplesPerVector=1, double unitaryLength = 1, bool relative = false, double angleScale = 1.0f);

		~Buffer<T>();

		/*size_t size();
		T& at(size_t _Pos);

		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrbegin();
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrend();*/

		sp::result operator()();


	private:
		std::vector<T>* buf;
		int _samplesPerVector,_showSamples;
		double _unitaryLength;
		bool _relative;
		double _angleScale;
		//std::pair<std::pair<double, double>, std::pair<double, double>> _center;
	};
}