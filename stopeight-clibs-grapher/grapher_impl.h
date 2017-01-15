#pragma once

#include <vector>

namespace grapher {

	template<typename T>class Buffer
	{
	public:
		Buffer<T>(const T* storage,size_t size);
		~Buffer<T>();

		size_t size();
		T& at(size_t _Pos);

		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrbegin();
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> rmrend();

		//template<typename... stl_args, typename=Enable_if<sizeof...(stl_args)==0> >void execute_stl(void(*_func)(stl_args...),stl_args... _a);
		void execute_stl();


	private:
		std::vector<T> buf;
	};
}