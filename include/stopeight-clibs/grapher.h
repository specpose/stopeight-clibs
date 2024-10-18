// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include <vector>
#include <stopeight-clibs/shared_types.h>

namespace speczilla {

	template<typename T>class VectorGraph
	{
	public:
		VectorGraph<T>(std::vector<T>* s);
		explicit VectorGraph<T>(std::vector<T>* s, size_t showSamples, size_t samplesPerVector=1, double unitaryLength = 1, bool relative = false, double average = 0.0f, double angleScale = 1.0f);

		~VectorGraph<T>();

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