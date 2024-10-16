// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include <vector>
#include <stackable-functor-allocation/sfa.hpp>
#include <stopeight-clibs/shared_types.h>

namespace speczilla {

	template<typename T>class VectorGraph2
	{
	public:
		VectorGraph2<T>(std::vector<T>* s);
		explicit VectorGraph2<T>(std::vector<T>* s, size_t showSamples, size_t samplesPerVector=1, double unitaryLength = 1, bool relative = false, double average = 0.0f, double angleScale = 1.0f);

		~VectorGraph2<T>();

		std::vector<sp::timecode<T>> operator()();

	private:
		std::vector<T>* buf;
		std::vector<sp::timecode<T>> output;
		size_t _samplesPerVector,_showSamples;
		double _unitaryLength;
		bool _relative;
		double _average;
		double _angleScale;
	};
}