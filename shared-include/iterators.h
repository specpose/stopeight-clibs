// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ITERATORS_H
#define ITERATORS_H

namespace stopeight {
	//has to be random access; is forward
	template<typename IteratorType> class block_iterator : public std::iterator<std::forward_iterator_tag,
																				std::pair<IteratorType,IteratorType> > {
		//typedef typename std::iterator::iterator_category iterator_category;
		//typedef typename std::iterator::value_type value_type;
		//typedef typename _Iter::difference_type difference_type;
		//typedef typename _Iter::pointer pointer;
		//typedef typename _Iter::reference reference;
	public:
		// std::distance
		// end: modulus
		// constructor from start
		// constructor from end
		// iterator->endgetter?
		explicit block_iterator(IteratorType rand, IteratorType rand2, const int seg_size) : _first(rand), _last(rand2), _pos(0), _seg_size(seg_size) {};
		//const, arg const
		bool operator==(block_iterator<IteratorType>& b) {
			std::pair<IteratorType, IteratorType> a = construct();
			//if ((a.first = b.first) && (a.second == b.second))
			if ((*a->first == *(*be).first) && (*a->second == *(*be).second))
				return true;
			return false;
		};
		//const, arg const
		bool operator!=(block_iterator<IteratorType>& be) {
			std::pair<IteratorType, IteratorType>* a = construct();
			if ( (*a->first != *(*be).first) || (*a->second != *(*be).second) )
				return true;
			return false;
		};
		block_iterator<IteratorType>& operator++() {
			block_iterator<IteratorType> tmp = *this;
			_pos += _seg_size;
			return tmp;
		};
		block_iterator<IteratorType> operator++(int i) {
			_pos += i*_seg_size;
			return this;
		};
		//const
		std::pair<IteratorType, IteratorType>& operator*() {
			std::pair<IteratorType, IteratorType>& a = *(construct());
			return a;
		};
		//const
		std::pair<IteratorType, IteratorType>* operator->() {
			std::pair<IteratorType, IteratorType>* a = construct();
			return a;
		};
		//This should be in container or independent function
		//full iterator with pos set from outside,
		//or short iterator with pos=0
		block_iterator end() {
			return blockiterator<IteratorType>(_first, _first, _seg_size);
			/*int d = std::distance(_first, _last)
			int i = d / _seg_size;
			IteratorType current,end;
			if (remainder() == 0)
				current = _first + (i - 1)*_seg_size;
			else
				current = _first + (i)*_seg_size;*/
		}


	private:
		//std::distance
		bool _legalPos() { return ((_first + _pos) < _last); };
		int remainder() { return std::distance(_first, _last) % _seg_size; };
		std::pair<IteratorType, IteratorType>* construct() {
			auto current = _first + _pos;
			auto end = current;
			if (_legalPos()) {
				if (std::distance(_first + _pos, _last) >= _seg_size)
					end += _seg_size;
				else
					end += remainder();
			}
			else {
				current, end = _last;
			}
			return new std::pair<IteratorType, IteratorType>{current,end};
		};
		IteratorType _first,_last;
		int _pos, _seg_size;
	};
}
#endif