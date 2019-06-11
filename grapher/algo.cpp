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
    template<class InputIterator = std::enable_if<std::is_base_of<std::random_access_iterator_tag, std::iterator_traits<T>::iterator_category>::value && std::is_arithmetic<std::iterator_traits<T>::value_type>::value, T>, class OutputIterator> void __differences(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
        std::adjacent_difference(begin, end, begin2);
        //*std::begin(differences) = 0;
    }
    template void __differences(std::vector<double>::iterator, std::vector<double>::iterator, std::vector<double>::iterator) ;
    template void __differences(std::vector<float>::iterator, std::vector<float>::iterator, std::vector<float>::iterator);
	template void __differences(std::vector<int16_t>::iterator, std::vector<int16_t>::iterator, std::vector<int16_t>::iterator);
	
	template<class InputIterator = std::enable_if<std::is_base_of<std::input_iterator_tag, std::iterator_traits<T>::iterator_category>::value && std::is_arithmetic<std::iterator_traits<T>::value_type>::value, T>, class OutputIterator> void __calculate_rotations(InputIterator begin, InputIterator end, OutputIterator begin2, angle::angle& angleFunction)
    {
		using T = decltype(*begin);//todo remove back_inserter -> decltype(*begin2)
        std::transform(begin, end, begin2, [&angleFunction](T diff) {
            return angleFunction(diff);
        });
    }
    template void __calculate_rotations(std::vector<double>::iterator, std::vector<double>::iterator, std::back_insert_iterator<std::vector<double>>, angle::angle&);
	template void __calculate_rotations(std::vector<float>::iterator, std::vector<float>::iterator, std::back_insert_iterator<std::vector<float>>, angle::angle&);
    
    template<class InputIterator = std::enable_if<std::is_base_of<std::random_access_iterator_tag, std::iterator_traits<T>::iterator_category>::value && std::is_arithmetic<std::iterator_traits<T>::value_type>::value, T>, class OutputIterator> void __apply_rotation_matrix(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
		using OutputElement = typename std::iterator_traits<OutputIterator>::value_type;
		using T = typename OutputElement::value_type;

        std::transform(begin, end, begin2, begin2, [](T rot, OutputElement vec) {
            T x = (cos(rot)*vec.get_x() - sin(rot)*vec.get_y());
            T y = (sin(rot)*vec.get_x() + cos(rot)*vec.get_y());
			auto p = OutputElement{ T(x) , T(y) };
            return p;
        });
    }
    template void __apply_rotation_matrix(std::vector<double>::iterator begin, std::vector<double>::iterator end, sp::result<double>::iterator begin2);
	template void __apply_rotation_matrix(std::vector<float>::iterator begin, std::vector<float>::iterator end, sp::result<float>::iterator begin2);

    _fixpoints::_fixpoints(std::vector<size_t>& points) : _fixPoint_indices(points) {
    }
    _fixpoints::~_fixpoints() {
    }
    template <class InputIterator = sp::random_access<InputIterator>, class OutputIterator> void _fixpoints::operator()(InputIterator begin, InputIterator end, OutputIterator begin2)
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
		using T = std::iterator_traits<InputIterator>::value_type::value_type;//todo remove backinserter//std::iterator_traits<std::iterator_traits<OutputIterator>::first_type>::value_type::value_type;
        std::transform(std::begin(slices), std::end(slices), begin2, [begin](std::pair<size_t, size_t> p) {
            it_element<T> e = it_element<T>();
            e.first = (begin + p.first);
            e.second = (begin + p.second);
            return e;
        });
    }
    template void _fixpoints::operator()(sp::result<double>::iterator begin, sp::result<double>::iterator end, std::vector<it_element<double>>::iterator begin2);
	template void _fixpoints::operator()(sp::result<float>::iterator begin, sp::result<float>::iterator end, std::vector<it_element<float>>::iterator begin2);

    _blocks::_blocks(int samplesPerVector) : _samplesPerVector(samplesPerVector) {
        
    }
    _blocks::~_blocks() {
        
    }
    template <class ExecutionPolicy, class InputIterator, class OutputIterator> void _blocks::operator()(ExecutionPolicy& task1, InputIterator begin, InputIterator end, OutputIterator begin2, std::random_access_iterator_tag)
    {
		using T = vector_vectors_T<InputIterator>;
        auto spV = _samplesPerVector;
        std::for_each(begin, end, [&begin2, spV](it_element<T> slice) {
            auto size = std::distance(slice.first, slice.second);
            if (size > 0) {
                auto sectionend = (spV > size) ? size : spV;
                for (int i = 0; i < (size / sectionend); i++) {
                    *begin2++ = (it_element<T>{ (slice.first + (i*sectionend)),(slice.first + (i*sectionend) + sectionend) });
                }
                auto remainder = size%sectionend;
                if (remainder != 0)
                    *begin2++ = (it_element<T>{ (slice.second - remainder),slice.second });
            }
            else {
                *begin2++ = (it_element<T>{ slice.first, slice.first });
            }
        });
    }
    template void _blocks::operator()(fexec& task1, vector_vectors<double> begin, vector_vectors<double> end, vector_vectors<double> begin2, std::random_access_iterator_tag);
	template void _blocks::operator()(fexec& task1, vector_vectors<float> begin, vector_vectors<float> end, vector_vectors<float> begin2, std::random_access_iterator_tag);
  
    
    template <class ExecutionPolicy, class InputIterator, class OutputIterator> void _sum_blocks::operator()(ExecutionPolicy& task1, InputIterator begin, InputIterator end, OutputIterator begin2, std::random_access_iterator_tag)
    {
		using T = vector_vectors_T<InputIterator>;//?!
        //transforming intput it_element to sp:element
        std::transform(begin, end, begin2, [](it_element<T> block) {
            //both can be nonempty; preserve type of last
            if (block.first != block.second) {
				const sp::timecode<T> e = sp::timecode<T>{ 0,0 };
                return std::accumulate(block.first, block.second, e, [](sp::timecode<T> v1, sp::timecode<T> v2) {
                    v2 += v1;
                    return v2;
                });
            }
            else {
                //auto v = sp::construct_element((*block.first)->first, (*block.first)->second);
				sp::timecode<T> v = *block.first;
                return v;//second could be last+1
            }
        });
    }
    template void _sum_blocks::operator()(fexec& task1, vector_vectors<double> begin, vector_vectors<double> end, vector_pair<double> begin2, std::random_access_iterator_tag);
    template void _sum_blocks::operator()(fexec& task1, vector_vectors<float> begin, vector_vectors<float> end, vector_pair<float> begin2, std::random_access_iterator_tag);
    
    template <class ExecutionPolicy, class InputIterator, class OutputIterator> void _append::operator()(ExecutionPolicy& task1, InputIterator begin, InputIterator end, OutputIterator begin2, std::forward_iterator_tag)
    {
		using T = vector_pair_T<OutputIterator>;
        class my_add {
        public:
			my_add() : cache(sp::timecode<T>{0, 0}) {};
            sp::timecode<T> operator()(sp::timecode<T> e) {
                auto newvalue = e;//type preserved
                newvalue += cache;//type preserved
                cache += e;//type mutating
                return newvalue;
            };
        private:
            sp::timecode<T> cache;
        };
        std::transform(begin, end, begin2, my_add());
    }
    template void _append::operator()(fexec& task1, vector_pair<double> begin, vector_pair<double> end, vector_pair<double> begin2, std::forward_iterator_tag);
	template void _append::operator()(fexec& task1, vector_pair<float> begin, vector_pair<float> end, vector_pair<float> begin2, std::forward_iterator_tag);
    
    __differences_To_VG::__differences_To_VG(int samplesPerVector, double vectorLength, std::vector<size_t> fixPoints_indices)
    : _samplesPerVector(samplesPerVector)
    , _vectorLength(vectorLength)
    , _fixPoint_indices(fixPoints_indices)
    {
    }
    __differences_To_VG::~__differences_To_VG() {
    }
    //partial specialization
    template <class ExecutionPolicy, class InputIterator, class OutputIterator, class UnaryFunction> void __differences_To_VG::operator()(ExecutionPolicy& task1, InputIterator begin, InputIterator end, OutputIterator begin2, UnaryFunction& angleFunction)
    {
		using T = vector_single_T<InputIterator>;//?!
        //par
        //std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });
        
        std::vector<T> rotations;
        //first one is invalid
        //Windows __calculate_rotations()(task1, begin, end, std::back_inserter(rotations), angleFunction, InputIterator::iterator_category{});
        __calculate_rotations(begin, end, std::back_inserter(rotations), angleFunction);
        
        sp::result<T> vectors;
		std::fill_n(std::back_inserter(vectors), std::distance(std::begin(rotations), std::end(rotations)), sp::timecode<T>{T(_vectorLength), 0});
        __apply_rotation_matrix(std::begin(rotations), std::end(rotations), std::begin(vectors));
        
        std::vector<it_element<T>> vectors_sliced;
        auto func = _fixpoints(_fixPoint_indices);
        //Windows func(task1, std::begin(vectors), std::end(vectors), std::back_inserter(vectors_sliced), InputIterator::iterator_category{});
        func(std::begin(vectors), std::end(vectors), std::back_inserter(vectors_sliced));
        
        sp::result<T> out_vectors;
        
        /*
         //HERESTART
         std::vector<it_element> blocks;
         _blocks(_samplesPerVector)(task1, std::begin(vectors_sliced), std::end(vectors_sliced), std::back_inserter(blocks), InputIterator::iterator_category{});
         
         std::vector<sp::element> sums;
         _sum_blocks()(task1, std::begin(blocks), std::end(blocks), std::back_inserter(sums), InputIterator::iterator_category{});
         
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
            
            //Windows _sum_blocks()(task1, std::begin(blocks_vector), std::end(blocks_vector), std::back_inserter(ov), InputIterator::iterator_category{});
            _sum_blocks()(task1, std::begin(blocks_vector), std::end(blocks_vector), std::back_inserter(ov), typename InputIterator::iterator_category{});
            std::move(std::begin(ov), std::end(ov), std::back_inserter(out_vectors));
        }
        //});
        
        //Windows _append()(task1, std::begin(out_vectors), std::end(out_vectors), std::begin(out_vectors), InputIterator::iterator_category{});
        _append()(task1, std::begin(out_vectors), std::end(out_vectors), std::begin(out_vectors), typename InputIterator::iterator_category{});
        
        std::copy<typename sp::result<T>::iterator, OutputIterator>(std::begin(out_vectors), std::end(out_vectors), begin2);
    }
    //void grapher::__differences_To_VG::operator()<dummy const, std::__1::__wrap_iter<double*>, std::__1::__wrap_iter<sp::timecode<double>*>, angle::averageScaled>(dummy const&, std::__1::__wrap_iter<double*>, std::__1::__wrap_iter<double*>, std::__1::__wrap_iter<sp::timecode<double>*>, angle::averageScaled&);
    template void __differences_To_VG::operator()(fexec& task1, vector_single<double> begin, vector_single<double> end, vector_pair<double> begin2, angle::angle& angleFunction);
    template void __differences_To_VG::operator()(fexec& task1, vector_single<float> begin, vector_single<float> end, vector_pair<float> begin2, angle::angle& angleFunction);
	template void __differences_To_VG::operator()(fexec& task1, vector_single<double> begin, vector_single<double> end, std::back_insert_iterator<sp::result<double>> begin2, angle::angle& angleFunction);
	template void __differences_To_VG::operator()(fexec& task1, vector_single<float> begin, vector_single<float> end, std::back_insert_iterator<sp::result<float>> begin2, angle::angle& angleFunction);
	template void __differences_To_VG::operator()(fexec& task1, vector_single<int16_t> begin, vector_single<int16_t> end, std::back_insert_iterator<sp::result<int16_t>> begin2, angle::angle& angleFunction);
    
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
    
    samples_To_VG::samples_To_VG(int samplesPerVector, double vectorLength, std::vector<size_t> fixPoints_indices)
    : _samplesPerVector(samplesPerVector)
    , _vectorLength(vectorLength)
    , _fixPoint_indices(fixPoints_indices)
    {
    }
    samples_To_VG::~samples_To_VG() {
    }
    //partial specialization
    template <class ExecutionPolicy, class InputIterator, class OutputIterator, class UnaryFunction> void samples_To_VG::operator()(ExecutionPolicy& task1, InputIterator begin, InputIterator end, OutputIterator begin2, UnaryFunction& angleFunction)
    {
		using T = vector_pair_T<OutputIterator>;
        //par
        //std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });
        size_t size = std::distance(begin, end);
        if (size > 0) {
            std::vector<T> differences = std::vector<T>(size, 0);
            __differences(begin, end, std::begin(differences));
            
            __differences_To_VG(_samplesPerVector, _vectorLength, _fixPoint_indices)(task1, std::begin(differences) + 1, std::end(differences), begin2, angleFunction);
        }
    }
    template void samples_To_VG::operator()(fexec& task1, vector_single<float> begin, vector_single<float> end, vector_pair<float> begin2, angle::angle& angleFunction);
    template void samples_To_VG::operator()(fexec& task1, vector_single<double> begin, vector_single<double> end, vector_pair<double> begin2, angle::angle& angleFunction);
    
}

//weird double defined symbol error for sycl::device from msvc
//msvc compile
//#include "shared_types.cpp"
