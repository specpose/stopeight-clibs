// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef CONTAINERS_H
#define CONTAINERS_H

namespace stopeight {
	//has to be sequential, random access to avoid copy
	template<typename DataType>
	//enable_if check for contiguous allocation, ie. std::vector::iterator
	class blocks : public std::vector<std::pair<typename std::vector<DataType>::iterator, typename std::vector<DataType>::iterator>> {
	public:
		explicit blocks(std::vector<DataType>&& vec, const int seg_size = 1)
			: _seg_size(seg_size)
			, std::vector<std::pair<typename std::vector<DataType>::iterator, typename std::vector<DataType>::iterator>>(calculateSize(vec.size(), seg_size))
			, _vec{ vec }
		{
			int n = 0;
			int o = this->size()-1;
			int _endFull = endFull(_vec.size(), _seg_size);
			for (int i = seg_size; i <= _endFull; i += seg_size) {
				auto v = std::pair<std::vector<DataType>::iterator, std::vector<DataType>::iterator>(std::begin(_vec) + i - seg_size, std::begin(_vec) + i - 1);
				this->at(n++) = v;
			}
			if (_endFull != _vec.size()) {
				auto l = _vec.size() - _endFull;
				auto v = std::pair<std::vector<DataType>::iterator, std::vector<DataType>::iterator>(std::end(_vec) - l, std::end(_vec) - 1);
				this->at(o) = v;
			}
		};

		static int calculateSize(int vec_size, int seg_size) {
			if (vec_size >= seg_size) {
				if ((vec_size%seg_size) == 0) {
					return vec_size / seg_size;
				}
				else {
					return (vec_size / seg_size) + 1;
				}
			}
			else {
				return 1;
			}
		};

	private:
		//needed in initializer
		static int endFull(int vec_size, int seg_size) {
			if ((vec_size % seg_size) == 0)
				return vec_size;
			else
				return vec_size - (vec_size%seg_size);
		}
		std::vector<DataType> _vec;
		int _seg_size;
	};
}
#endif