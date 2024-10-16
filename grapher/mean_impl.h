// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include <vector>

#include <stopeight-clibs/shared_types.h>

namespace speczilla {

	template<typename T>class Mean
	{
	public:
		Mean<T>(std::vector<T>* s);

		~Mean<T>();

		double operator()();


	private:
		std::vector<T>* buf;
	};
}