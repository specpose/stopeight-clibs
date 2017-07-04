// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#pragma once

namespace Speczilla {
	class PCMSource {
	public:
		PCMSource(size_t size)
		template<typename Datatype> size_t read(std::vector<Datatype>& buffer, size_t offset);

	};
}

namespace stopeight {

	//sometypeiterator(stlargs)
	//NO ExecutionPolicy, plain STL
	//using stl_function = void(IControlListener::*)(CControl*);
	using stl_function = template<typename... Args>void()(Args);

	template<typename T>class DMALoader
	{
	public:
		//make whole class functor?
		DMALoader(PCMSource source);
		~DMALoader();

		size_t getSize();
		//make sycl iterator
		//call function from below with sycliterator
		void execute(stl_function func);

	private:

		PCMSource buf;
	};
}