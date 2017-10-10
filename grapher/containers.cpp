// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "containers.h"
#include <stopeight-clibs/shared_types.h>

namespace stopeight {

	template<typename DataType> blocks<DataType>::blocks(stopeight::bounds<DataType> vec, const int seg_size)
			: std::vector<bounds<DataType>>(mySize(vec,seg_size))
			, _vec{ vec }
			, _seg_size(seg_size)
		{
			int origin_size = std::distance(_vec.first,_vec.second);//_vec.size();
			int n = 0;
			int o = this->size()-1;
			int _endFull = endFull(origin_size, _seg_size);
			for (int i = seg_size; i <= _endFull; i += seg_size) {
                //Windows auto v = std::pair<std::vector<DataType>::iterator, std::vector<DataType>::iterator>(_vec.first + i - seg_size, _vec.first + i - 1);
				auto v = std::pair<typename std::vector<DataType>::iterator, typename std::vector<DataType>::iterator>(_vec.first + i - seg_size, _vec.first + i - 1);
				this->at(n++) = v;
			}
			if (_endFull != origin_size) {
				auto l = origin_size - _endFull;
                //Windows auto v = std::pair<std::vector<DataType>::iterator, std::vector<DataType>::iterator>(_vec.second - l, _vec.second - 1);
				auto v = std::pair<typename std::vector<DataType>::iterator, typename std::vector<DataType>::iterator>(_vec.second - l, _vec.second - 1);
				this->at(o) = v;
			}
		};
	template blocks<sp::timecode<double>>::blocks(stopeight::bounds<sp::timecode<double>> vec, const int seg_size);
	template blocks<sp::timecode<float>>::blocks(stopeight::bounds<sp::timecode<float>> vec, const int seg_size);

	template<typename DataType> int blocks<DataType>::calculateSize(int vec_size, int seg_size) {
			if (vec_size > seg_size) {
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
		

		template<typename DataType> int blocks<DataType>::mySize(const bounds<DataType> vec, int seg_size) {
			// a fixpoint in a block of 1 can not be separated
			//auto a = addedFixPoints(vec);
			auto x = calculateSize(std::distance(vec.first,vec.second), seg_size);
			// we need at least one more than total number of fixpoints
			//if (x > a)
			//	return x+a;
			//else
			return x;
		}
		//needed in initializer
		template<typename DataType> int blocks<DataType>::endFull(int vec_size, int seg_size) {
			if ((vec_size % seg_size) == 0)
				return vec_size;
			else
				return vec_size - (vec_size%seg_size);
		}
		

//	template<typename DataType> int blocks<DataType>::addedFixPoints(const bounds<DataType> vec) {
//		return 0;
//	}

//#include "shared_types.h"
//	template<> int blocks<sp::element>::addedFixPoints(const bounds<sp::element> vec){
//		return std::count_if(vec.first, vec.second, [](sp::element& t) {
//			//return !sp::is<sp::empty<sp::element::value_type>>(dynamic_cast<sp::element*>(t));
//			return t->category == sp::tctype::FIXPOINT; 
//		});
//	}
};
