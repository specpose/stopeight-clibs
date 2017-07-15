// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <vector>

namespace stopeight {
	template<typename DataType> using bounds = std::pair<typename std::vector<DataType>::iterator, typename std::vector<DataType>::iterator>;

	//has to be sequential, random access to avoid copy
	template<typename DataType>
	//enable_if check for contiguous allocation, ie. std::vector::iterator
	class blocks : public std::vector<bounds<DataType>> {
	public:
		explicit blocks(bounds<DataType> vec, const int seg_size = 1);

		static int calculateSize(int vec_size, int seg_size);
		

	private:
		static int mySize(const bounds<DataType> vec, int seg_size);
		//needed in initializer
		static int endFull(int vec_size, int seg_size);
		//static int addedFixPoints(const bounds<DataType> vec);
		bounds<DataType> _vec;
		int _seg_size;
	};
}
#endif
