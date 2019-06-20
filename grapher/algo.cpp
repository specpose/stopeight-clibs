// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

//#include <experimental/algorithm>//CYCLIC DEPENDENCY
#include <stopeight-clibs/shared_types.h>//CYCLIC DEPENDENCY
//#include <experimental/impl/algorithm_impl.h>
//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = const dummy;

#include "algo_impl.h"
#include "containers.h"
//#include "iterators.h"

//double define
//#include <experimental/execution_policy>

#include <algorithm>

#include <vector>
#include <math.h>

namespace grapher {
    template<class InputIterator,
		class OutputIterator,
		typename>
		void __differences(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
        std::adjacent_difference(begin, end, begin2);
        //*std::begin(differences) = 0;
    }
    template void __differences(std::vector<double>::iterator, std::vector<double>::iterator, std::vector<double>::iterator) ;
    template void __differences(std::vector<float>::iterator, std::vector<float>::iterator, std::vector<float>::iterator);
	template void __differences(std::vector<int16_t>::iterator, std::vector<int16_t>::iterator, std::vector<int16_t>::iterator);
	
	template<class InputIterator,
		class OutputIterator,
		typename
	>
		void __calculate_rotations(InputIterator begin, InputIterator end, OutputIterator begin2, sp::sharing_functor<double,double>& angleFunction)
    {
		using T = typename std::iterator_traits<InputIterator>::value_type;//todo remove back_inserter -> std::iterator_traits<OutputIterator>::value_type;
        std::transform(begin, end, begin2, [&angleFunction](T diff) {
            return angleFunction(diff);
        });
    }
	template void __calculate_rotations(std::vector<double>::iterator, std::vector<double>::iterator, std::vector<double>::iterator, sp::sharing_functor<double,double>&);
	template void __calculate_rotations(std::vector<float>::iterator, std::vector<float>::iterator, std::vector<float>::iterator, sp::sharing_functor<double,double>&);
	template void __calculate_rotations(std::vector<int16_t>::iterator, std::vector<int16_t>::iterator, std::vector<int16_t>::iterator, sp::sharing_functor<double,double>&);
    
	//todo make par_unseq
	template<class InputIterator,
		class OutputIterator,
		typename
	>
		void __calculate_rotations(InputIterator begin, InputIterator end, OutputIterator begin2, sp::readonly_functor<double,double>& angleFunction)
	{
		using T = typename std::iterator_traits<InputIterator>::value_type;//todo remove back_inserter -> std::iterator_traits<OutputIterator>::value_type;
		std::transform(begin, end, begin2, [&angleFunction](T diff) {
			return angleFunction(diff);
		});
	}
	template void __calculate_rotations(std::vector<double>::iterator, std::vector<double>::iterator, std::vector<double>::iterator, sp::readonly_functor<double,double>&);
	template void __calculate_rotations(std::vector<float>::iterator, std::vector<float>::iterator, std::vector<float>::iterator, sp::readonly_functor<double,double>&);
	template void __calculate_rotations(std::vector<int16_t>::iterator, std::vector<int16_t>::iterator, std::vector<int16_t>::iterator, sp::readonly_functor<double,double>&);


    template<class InputIterator
		, class OutputIterator,
		typename> void __apply_rotation_matrix(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
		using OutputElement = typename std::iterator_traits<OutputIterator>::value_type;
		using T = typename OutputElement::value_type;

        std::transform(begin, end, begin2, begin2, [](T rot, OutputElement vec) {
            T x = (cos(rot)*vec.get_x() - sin(rot)*vec.get_y());
            T y = (sin(rot)*vec.get_x() + cos(rot)*vec.get_y());
			auto p = OutputElement{};
			p.__init();
			p.set_x(x);
			p.set_y(y);
            return p;
        });
    }
    template void __apply_rotation_matrix(std::vector<double>::iterator begin, std::vector<double>::iterator end, sp::result<double>::iterator begin2);
	template void __apply_rotation_matrix(std::vector<float>::iterator begin, std::vector<float>::iterator end, sp::result<float>::iterator begin2);

    _fixpoints::_fixpoints(std::vector<size_t>& points) : _fixPoint_indices(points) {
    }
    _fixpoints::~_fixpoints() {
    }
    template <class InputIterator,
		class OutputIterator,
		typename> void _fixpoints::operator()(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
        //remove all illegal fixpoint_indices
        //Note: last can not be fixPoint
        const auto vectors_size = std::distance(begin, end);
        std::remove_if(std::begin(_fixPoint_indices), std::end(_fixPoint_indices), [vectors_size](size_t index) {
            if ((index >= (vectors_size - 1)) || (index == 0))
                return true;
            return false;
        });
        //make it a fixPoint
        for (auto index : _fixPoint_indices) {
			(begin + index)->set_category(sp::FixpointType::FIXPOINT);
        }
        std::vector<std::pair<size_t, size_t>> slices = std::vector<std::pair<size_t, size_t>>{};
        class prev {
        public:
            prev() : _prev(0) {};
            std::pair<size_t, size_t> operator()(size_t curr) {
                auto result = std::pair<size_t, size_t>{ _prev,curr };
                _prev = curr + 1;
                return result;
            };
        private:
            size_t _prev;
        };
        auto it = std::back_inserter(slices);
        std::for_each(std::begin(_fixPoint_indices), std::end(_fixPoint_indices), [&it](size_t index) {
            *it++ = (prev()(index));//was index
            *it++ = (std::pair<size_t, size_t>{index, index + 1});//was index+1
        });
        //tail end
        std::pair<size_t, size_t> last = std::pair<size_t, size_t>{ 0,vectors_size };
        if (vectors_size > 0) {
            last = std::pair<size_t, size_t>{ _fixPoint_indices.back() + 1, vectors_size };// was _fixPoint_indices.back() + 1
        }
        *it++ = (last);
		using T = typename std::iterator_traits<InputIterator>::value_type::value_type;//todo remove backinserter//std::iterator_traits<std::iterator_traits<OutputIterator>::value_type::first_type>::value_type::value_type;

        std::transform(std::begin(slices), std::end(slices), begin2, [begin](std::pair<size_t, size_t> p) {//todo derive sp::it_pair
            sp::it_pair<T> e = sp::it_pair<T>();
            e.first = (begin + p.first);
            e.second = (begin + p.second);
            return e;
        });
    }
    template void _fixpoints::operator()(sp::result<double>::iterator begin, sp::result<double>::iterator end, std::vector<sp::it_pair<double>>::iterator begin2);
	template void _fixpoints::operator()(sp::result<float>::iterator begin, sp::result<float>::iterator end, std::vector<sp::it_pair<float>>::iterator begin2);

    _blocks::_blocks(size_t samplesPerVector) : _samplesPerVector(samplesPerVector) {
        
    }
    _blocks::~_blocks() {
        
    }
    template <class InputIterator, class OutputIterator> void _blocks::operator()(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
		using it_pair = typename std::iterator_traits<OutputIterator>::value_type;
		auto spV = _samplesPerVector;
        std::for_each(begin, end, [&begin2, spV](it_pair slice) {
            auto size = std::distance(slice.first, slice.second);
            if (size > 0) {
                auto sectionend = (spV > size) ? size : spV;
                for (int i = 0; i < (size / sectionend); i++) {
                    *begin2++ = (it_pair{ (slice.first + (i*sectionend)),(slice.first + (i*sectionend) + sectionend) });
                }
                auto remainder = size%sectionend;
                if (remainder != 0)
                    *begin2++ = (it_pair{ (slice.second - remainder),slice.second });
            }
            else {
                *begin2++ = (it_pair{ slice.first, slice.first });
            }
        });
    }
    template void _blocks::operator()(std::vector<sp::it_pair<double>>::iterator begin, std::vector<sp::it_pair<double>>::iterator end, std::vector<sp::it_pair<double>>::iterator begin2);
	template void _blocks::operator()(std::vector<sp::it_pair<float>>::iterator begin, std::vector<sp::it_pair<float>>::iterator end, std::vector<sp::it_pair<float>>::iterator begin2);

    
    template <class InputIterator, class OutputIterator> void _sum_blocks(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
		using it_pair = typename std::iterator_traits<InputIterator>::value_type;//vector of pairs -> pair//sp::it_pair not available from OutputIterator
		using tc = typename it_pair::first_type::value_type;//pair -> tc -> T
		//transforming intput sp::it_pair to sp:element
        std::transform(begin, end, begin2, [](it_pair block) {
            //both can be nonempty; preserve type of last
            if (block.first != block.second) {
				tc e {};
				e.__init();
                return std::accumulate(block.first, block.second, e, [](tc v1, tc v2) {
                    v2 += v1;
                    return v2;
                });
            }
            else {
                //auto v = sp::construct_element((*block.first)->first, (*block.first)->second);
				tc v = *block.first;
                return v;//second could be last+1
            }
        });
    }
    template void _sum_blocks(std::vector<sp::it_pair<double>>::iterator begin, std::vector<sp::it_pair<double>>::iterator end, sp::result<double>::iterator begin2);
	template void _sum_blocks(std::vector<sp::it_pair<float>>::iterator begin, std::vector<sp::it_pair<float>>::iterator end, sp::result<float>::iterator begin2);

    template <class InputIterator,
		class OutputIterator,
		typename>
		void _append(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
		using tc = typename std::iterator_traits<OutputIterator>::value_type;
        class my_add {
        public:
			my_add() : cache({}) { cache.__init(); };
            tc operator()(tc e) {
                auto newvalue = e;//type preserved
                newvalue += cache;//type preserved
                cache += e;//type mutating
                return newvalue;
            };
        private:
            tc cache;
        };
        std::transform(begin, end, begin2, my_add());
    }
    template void _append(sp::result<double>::iterator begin, sp::result<double>::iterator end, sp::result<double>::iterator begin2);
	template void _append(sp::result<float>::iterator begin, sp::result<float>::iterator end, sp::result<float>::iterator begin2);

    template <class T> __differences_To_VG<T>::__differences_To_VG(size_t samplesPerVector, double vectorLength, std::vector<size_t> fixPoints_indices)
    : _samplesPerVector(samplesPerVector)
    , _vectorLength(vectorLength)
    , _fixPoint_indices(fixPoints_indices)
    {
    }
	template __differences_To_VG<double>::__differences_To_VG(size_t,double, std::vector<size_t>);
	template __differences_To_VG<float>::__differences_To_VG(size_t, double, std::vector<size_t>);
	template __differences_To_VG<int16_t>::__differences_To_VG(size_t, double, std::vector<size_t>);

	template <class T> __differences_To_VG<T>::~__differences_To_VG() {
    }
	template __differences_To_VG<double>::~__differences_To_VG();
	template __differences_To_VG<float>::~__differences_To_VG();
	template __differences_To_VG<int16_t>::~__differences_To_VG();

	template <class T> template <
		class UnaryFunction,
		typename
	> sp::result<T> __differences_To_VG<T>::operator()(std::vector<T>& differences, UnaryFunction& angleFunction)
    {
        //par
        //std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });
        
        std::vector<T> rotations;
        //first one is invalid
        __calculate_rotations(std::begin(differences) + 1, std::end(differences), std::back_inserter(rotations), angleFunction);
        
        sp::result<T> vectors;
		auto tc = sp::timecode<T>{};
		tc.__init();
		tc.set_x(_vectorLength);
		tc.set_y(0);
		std::fill_n(std::back_inserter(vectors), std::distance(std::begin(rotations), std::end(rotations)), tc);//sp::make_timecode<T>(T(_vectorLength), 0));//sp::timecode<T>{T(_vectorLength), 0});
        __apply_rotation_matrix(std::begin(rotations), std::end(rotations), std::begin(vectors));
        
        std::vector<sp::it_pair<T>> vectors_sliced;
        auto func = _fixpoints(_fixPoint_indices);
        func(std::begin(vectors), std::end(vectors), std::back_inserter(vectors_sliced));
        
		auto out_vectors = sp::result<T>{};//((vectorSize * 2) + add);
        
        /*
         //HERESTART
         std::vector<sp::it_pair> blocks;
         _blocks(_samplesPerVector)(task1, std::begin(vectors_sliced), std::end(vectors_sliced), std::back_inserter(blocks), InputIterator::iterator_category{});
         
         std::vector<sp::element> sums;
         _sum_blocks()(std::begin(blocks), std::end(blocks), std::back_inserter(sums));
         
         std::move(std::begin(sums), std::end(sums), std::back_inserter(out_vectors));
         //HEREEND
         */
        
        //hierarchy all to 1
        //std::transform(std::begin(vectors_sliced), std::end(vectors_sliced), std::back_inserter(out_vectors), [_samplesPerVector](decltype(vectors_sliced) v) {
        for (auto v : vectors_sliced) {
            stopeight::blocks<sp::timecode<T>> blocks_vector = stopeight::blocks<sp::timecode<T>>(v, _samplesPerVector);
            //std::move(slice), _samplesPerVector);
            
            sp::result<T> ov = sp::result<T>{};//(blocks_vector.size(), { double(0), double(0) });
            //std::fill<typename std::vector<sp::element>::iterator>(std::begin(ov), std::end(ov), sp::element{ 1.0f, 1.0f });
            
            _sum_blocks(std::begin(blocks_vector), std::end(blocks_vector), std::back_inserter(ov));
            std::move(std::begin(ov), std::end(ov), std::back_inserter(out_vectors));
        }
        //});
        
        _append(std::begin(out_vectors), std::end(out_vectors), std::begin(out_vectors));
        
		return out_vectors;
    }
	template sp::result<double> __differences_To_VG<double>::operator()(std::vector<double>&, angle::relative&);
	template sp::result<float> __differences_To_VG<float>::operator()(std::vector<float>&, angle::relative&);
	template sp::result<int16_t> __differences_To_VG<int16_t>::operator()(std::vector<int16_t>&, angle::relative&);
	template sp::result<double> __differences_To_VG<double>::operator()(std::vector<double>&, angle::independent&);
	template sp::result<float> __differences_To_VG<float>::operator()(std::vector<float>&, angle::independent&);
	template sp::result<int16_t> __differences_To_VG<int16_t>::operator()(std::vector<int16_t>&, angle::independent&);
    
    int samples_To_VG_vectorSize(int inputSize, int samplesPerVector) {
        auto size = inputSize / samplesPerVector;
        if (inputSize%samplesPerVector > 0)
            size++;
        return size;
        //return stopeight::blocks<sp::element>::calculateSize(inputSize, samplesPerVector);
    }
    
    double samples_To_VG_vectorLength(int showSamples, double unitaryLength) {
        return unitaryLength / showSamples;
    }
    
	template<class T> samples_To_VG<T>::samples_To_VG(size_t samplesPerVector, double vectorLength, std::vector<size_t> fixPoints_indices)
    : _samplesPerVector(samplesPerVector)
    , _vectorLength(vectorLength)
    , _fixPoint_indices(fixPoints_indices)
    {
    }
	template<class T> samples_To_VG<T>::~samples_To_VG() {
    }
    template<class T> template <class UnaryFunction> sp::result<T> samples_To_VG<T>::operator()(std::vector<T>& samples, UnaryFunction& angleFunction)
    {
        size_t size = std::distance(std::begin(samples), std::end(samples));
        if (size > 0) {
            std::vector<T> differences = std::vector<T>(size, 0);
            __differences(std::begin(samples), std::end(samples), std::begin(differences));
            
            return __differences_To_VG<T>(_samplesPerVector, _vectorLength, _fixPoint_indices)(differences, angleFunction);
        }
    }
    template sp::result<double> samples_To_VG<double>::operator()(std::vector<double>&, angle::sharing_angle&);
	template sp::result<float> samples_To_VG<float>::operator()(std::vector<float>&, angle::sharing_angle&);

}

//weird double defined symbol error for sycl::device from msvc
//msvc compile
//#include "shared_types.cpp"
