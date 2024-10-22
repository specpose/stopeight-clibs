// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

//#include <experimental/algorithm>//CYCLIC DEPENDENCY
#include <stopeight-clibs/shared_types.h>//CYCLIC DEPENDENCY

#include "stopeight-clibs/algo_gpx.h"
#include "containers.h"
//#include "iterators.h"

//double define
//#include <experimental/execution_policy>

#include <algorithm>
#include <iterator>

#include <vector>
#include <math.h>
#include "stopeight-clibs/error.hpp"

namespace grapher {

    //InputIterator = decltype(OutputIterator)<OutputElement::value_type>
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
			//p.__init({x,y});
            p.set_x(x);
            p.set_y(y);
            return p;
        });
    }
    template void __apply_rotation_matrix(std::vector<double>::iterator begin, std::vector<double>::iterator end, std::vector<sp::timecode<double>>::iterator begin2);
	template void __apply_rotation_matrix(std::vector<float>::iterator begin, std::vector<float>::iterator end, std::vector<sp::timecode<float>>::iterator begin2);

    _fixpoints::_fixpoints(std::vector<size_t>& points) : _fixPoint_indices(points) {
    }
    _fixpoints::~_fixpoints() {
    }
    template <class InputIterator,
		typename> void _fixpoints::operator()(InputIterator begin, InputIterator end)
    {
        /*//remove all illegal fixpoint_indices
        //Note: last can not be fixPoint
        const auto vectors_size = std::distance(begin, end);
        std::remove_if(std::begin(_fixPoint_indices), std::end(_fixPoint_indices), [vectors_size](size_t index) {
            if ((index >= (vectors_size - size_t(1) )) || (index == size_t(0) ))
                return true;
            return false;
        });*/
        //make it a fixPoint
        for (const auto& index : _fixPoint_indices) {
            if (index < std::distance(begin,end))
                (begin + index)->set_category(sp::FixpointType::FIXPOINT);
            else
                throw SFA::util::runtime_error("A fixpoint beyond the number of vectors in the VectorGraph has been found", __FILE__, __func__);
        }
    }
    template void _fixpoints::operator()(std::vector<sp::timecode<double>>::iterator begin, std::vector<sp::timecode<double>>::iterator end);
	template void _fixpoints::operator()(std::vector<sp::timecode<float>>::iterator begin, std::vector<sp::timecode<float>>::iterator end);
    template void _fixpoints::operator()(std::vector<sp::timecode<int16_t>>::iterator begin, std::vector<sp::timecode<int16_t>>::iterator end);

    template <class InputIterator, class OutputIterator> void _sum_blocks(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
		using it_pair = typename std::iterator_traits<InputIterator>::value_type;//vector of pairs -> pair//it_pair not available from OutputIterator
		using tc = typename it_pair::first_type::value_type;//pair -> tc -> T
		//transforming intput it_pair to sp:element
        std::transform(begin, end, begin2, [](it_pair block) {
            //both can be nonempty; preserve type of last
            if (block.first != block.second) {
				tc e {};
				//e.__init({0,0});
                e.set_x(0);
                e.set_y(0);
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
    template void _sum_blocks(std::vector<it_pair<double>>::iterator begin, std::vector<it_pair<double>>::iterator end, std::vector<sp::timecode<double>>::iterator begin2);
	template void _sum_blocks(std::vector<it_pair<float>>::iterator begin, std::vector<it_pair<float>>::iterator end, std::vector<sp::timecode<float>>::iterator begin2);

    template<typename output_t> _sum_blocks2<output_t>::_sum_blocks2(size_t samplesPerVector) :_samplesPerVector(samplesPerVector) {};//TODO: Align a grid of samplesPerVector to fixPoint
    template _sum_blocks2<float>::_sum_blocks2(size_t);
    template _sum_blocks2<double>::_sum_blocks2(size_t);
    template _sum_blocks2<int16_t>::_sum_blocks2(size_t);
    template<typename output_t> template<typename InputIterator>std::vector<sp::timecode<output_t>> _sum_blocks2<output_t>::operator()(const InputIterator begin, const InputIterator end){//, OutputIterator begin2) {
        std::vector<sp::timecode<output_t>> output(0);
        auto __fixpoint_tester = [](sp::timecode<output_t>& tct_point) {//const
            return (tct_point.category() == sp::FixpointType::FIXPOINT) ? true : false;
        };
        /*if (std::distance(begin, end) < _samplesPerVector)
            throw SFA::util::runtime_error("The requested samplesPerVector size is bigger than the number of input samples", __FILE__, __func__);
        auto number_of_fixpoints = std::count_if(begin, end, __fixpoint_tester);
        if (number_of_fixpoints == 0)
            throw SFA::util::runtime_error("This function needs more than zero Fixpoints", __FILE__, __func__);
        else if (number_of_fixpoints > 1)
            throw SFA::util::runtime_error("This function can not work with more than one Fixpoint", __FILE__, __func__);*/
        auto index_it = std::find_if(begin, end, __fixpoint_tester);
        InputIterator new_end = end;
        InputIterator new_beginning = begin;
        //The overhanging bits on either side are hacked of
        if (std::distance(begin, end) > 3 * _samplesPerVector) {//wing test
            //End should always point to the element after the last
            if (std::distance(index_it, end - 1) < _samplesPerVector) {//shift right
                new_beginning += std::distance(begin, end) % _samplesPerVector;
            }
            else if (std::distance(begin, index_it) < _samplesPerVector) {//shift left
                //hack off the rest
                new_end -= std::distance(begin, end) % _samplesPerVector;
            }
            else {//center
                new_beginning += int(std::distance(begin, end) % _samplesPerVector) / 2;//floor
                new_end -= int(std::distance(new_beginning, end) % _samplesPerVector) % 2;//floor
            }
        }
        else if (std::distance(begin, end) < 3 * _samplesPerVector) {
            throw SFA::util::runtime_error("The requested samplesPerVector and/or Fixpoint would result in a VectorGraph smaller than 3", __FILE__, __func__);
        }
        //if (int(std::distance(new_beginning, new_end) / _samplesPerVector) % 2 == 0)//floor
            //new_end = new_end - _samplesPerVector;//HACK
            //throw SFA::util::runtime_error("The requested samplesPerVector and/or Fixpoint would result in a VectorGraph with an even number of vectors", __FILE__, __func__);
        //The middle ones get promoted
        //for each _samplesPerVectors from the front:
        struct Promoter { std::array<InputIterator, 2> bounds{}; bool isFixpoint = false; };
        std::vector<Promoter> promotableBounds(0);
        //1. Create the bounds
        for (int i = 0; i < std::distance(new_beginning, new_end); i++) {
            for (int j = 0; j < std::distance(new_beginning, new_end) / _samplesPerVector; j++) {
                Promoter section{};
                std::get<0>(section.bounds) = new_beginning + _samplesPerVector * j;
                std::get<1>(section.bounds) = new_beginning + _samplesPerVector * (j + 1);
                section.isFixpoint = false;
                promotableBounds.push_back(section);
            }
        }
        auto test0 = std::distance(std::begin(promotableBounds),std::end(promotableBounds));
        //2. Extract the Fixpoint
        std::for_each(std::begin(promotableBounds), std::end(promotableBounds), [](auto& section) {
            for (int i = 0; i < std::distance(std::get<0>(section.bounds), std::get<1>(section.bounds)); i++)
                (std::get<0>(section.bounds) + i)->category() ? section.isFixpoint = true : section.isFixpoint = false;
            });
        //3. Sum them up in sequence and append to begin2
        //4. Promote the Fixpoint
        std::transform(std::begin(promotableBounds), std::end(promotableBounds), std::back_insert_iterator(output), [](const Promoter& section) {
            //std::transform(std::begin(promotableBounds), std::end(promotableBounds), begin2, [](const Promoter& section) {
            if (std::get<0>(section.bounds) != std::get<1>(section.bounds)) {
                sp::timecode<output_t> accumulator{};
                accumulator.set_x(0);
                accumulator.set_y(0);
                sp::timecode<output_t> blocksum = std::accumulate(std::get<0>(section.bounds), std::get<1>(section.bounds), accumulator,
                    [](sp::timecode<output_t> v1, sp::timecode<output_t> v2) {
                v2 += v1;
                return v2;
                    });
                if (section.isFixpoint)
                    blocksum.set_category(sp::FixpointType::FIXPOINT);
                return blocksum;
            }
            else {
                sp::timecode<output_t> accumulator{};
                accumulator = *std::get<0>(section.bounds);
                if (section.isFixpoint)
                    accumulator.set_category(sp::FixpointType::FIXPOINT);
                return accumulator;
            }
        });
        auto test1 = std::distance(std::begin(output), std::end(output));
        return output;
    };
    template std::vector<sp::timecode<float>> _sum_blocks2<float>::operator()(std::vector<sp::timecode<float>>::iterator, std::vector<sp::timecode<float>>::iterator);// , std::back_insert_iterator<std::vector<sp::timecode<float>>>);
    template std::vector<sp::timecode<double>> _sum_blocks2<double>::operator()(std::vector<sp::timecode<double>>::iterator, std::vector<sp::timecode<double>>::iterator);//, std::back_insert_iterator<std::vector<sp::timecode<double>>>);
    template std::vector<sp::timecode<int16_t>> _sum_blocks2<int16_t>::operator()(std::vector<sp::timecode<int16_t>>::iterator, std::vector<sp::timecode<int16_t>>::iterator);//, std::back_insert_iterator<std::vector<sp::timecode<int16_t>>>);

    template <class InputIterator,
		class OutputIterator,
		typename>
		void _append(InputIterator begin, InputIterator end, OutputIterator begin2)
    {
		using tc = typename std::iterator_traits<OutputIterator>::value_type;
        class my_add {
        public:
            my_add() : cache(tc{}) {
                cache.set_x(0); cache.set_y(0);
            };//cache.__init({0,0}); };
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
    template void _append(std::vector<sp::timecode<double>>::iterator begin, std::vector<sp::timecode<double>>::iterator end, std::vector<sp::timecode<double>>::iterator begin2);
	template void _append(std::vector<sp::timecode<float>>::iterator begin, std::vector<sp::timecode<float>>::iterator end, std::vector<sp::timecode<float>>::iterator begin2);

    template <class T> __differences_To_VG<T>::__differences_To_VG(size_t samplesPerVector, double vectorLength, std::vector<size_t> fixPoints_indices)
    : _samplesPerVector(samplesPerVector), _vectorLength(vectorLength)
    , _fixPoint_indices(fixPoints_indices)
    {
    }
	template __differences_To_VG<double>::__differences_To_VG(size_t, double, std::vector<size_t>);
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
	> std::vector<sp::timecode<T>> __differences_To_VG<T>::operator()(std::vector<T>& differences, UnaryFunction& angleFunction)
    {
        auto rotations = std::vector<T>(differences.size()-1);
        //first one is invalid
        std::transform(std::begin(differences) + 1, std::end(differences), std::begin(rotations), [&angleFunction](T diff) {
			return angleFunction(diff);
		});


		auto tc = sp::timecode<T>{};
		//tc.__init({T(_vectorLength),T(0)});
        tc.set_x(_vectorLength);//HACKED?
        tc.set_y(0);
        auto vectors = std::vector<sp::timecode<T>>(rotations.size());
		std::fill(std::begin(vectors), std::end(vectors), tc);//sp::make_timecode<T>(T(_vectorLength), 0));//sp::timecode<T>{T(_vectorLength), 0});
        __apply_rotation_matrix(std::begin(rotations), std::end(rotations), std::begin(vectors));
        
        //BUG No default constructor: iterator allocator? Workaround ranges::view
        //std::vector<std::pair< typename std::vector<sp::timecode<T>>::iterator, typename std::vector<sp::timecode<T>>::iterator >> vectors_sliced;
        auto func = _fixpoints(_fixPoint_indices);
        func(std::begin(vectors), std::end(vectors));
        grapher::_sum_blocks2<T> blocks(_samplesPerVector);
        auto output = blocks(std::begin(vectors), std::end(vectors));
        _append(std::begin(vectors), std::end(vectors), std::begin(vectors));
		return vectors;
    }
	template std::vector<sp::timecode<double>> __differences_To_VG<double>::operator()(std::vector<double>&, angle::relative&);
	template std::vector<sp::timecode<float>> __differences_To_VG<float>::operator()(std::vector<float>&, angle::relative&);
	template std::vector<sp::timecode<int16_t>> __differences_To_VG<int16_t>::operator()(std::vector<int16_t>&, angle::relative&);
	template std::vector<sp::timecode<double>> __differences_To_VG<double>::operator()(std::vector<double>&, angle::independent&);
	template std::vector<sp::timecode<float>> __differences_To_VG<float>::operator()(std::vector<float>&, angle::independent&);
	template std::vector<sp::timecode<int16_t>> __differences_To_VG<int16_t>::operator()(std::vector<int16_t>&, angle::independent&);
    
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
    : _samplesPerVector(samplesPerVector), _vectorLength(vectorLength)
    , _fixPoint_indices(fixPoints_indices)
    {
    }
    template samples_To_VG<double>::samples_To_VG(size_t, double,std::vector<size_t>);
    template samples_To_VG<float>::samples_To_VG(size_t, double,std::vector<size_t>);
	template<class T> samples_To_VG<T>::~samples_To_VG() {
    }
    template samples_To_VG<double>::~samples_To_VG();
    template samples_To_VG<float>::~samples_To_VG();
    template<class T> template <class UnaryFunction> std::vector<sp::timecode<T>> samples_To_VG<T>::operator()(std::vector<T>& samples, UnaryFunction& angleFunction)
    {
        size_t size = std::distance(std::begin(samples), std::end(samples));
        if (size > 0) {
            std::vector<T> differences = std::vector<T>(size, 0);
            std::adjacent_difference(std::begin(samples), std::end(samples), std::begin(differences));
            
            return __differences_To_VG<T>(_samplesPerVector, _vectorLength, _fixPoint_indices)(differences, angleFunction);
        }
    }
    template std::vector<sp::timecode<double>> samples_To_VG<double>::operator()(std::vector<double>&, angle::sharing_angle&);
	template std::vector<sp::timecode<float>> samples_To_VG<float>::operator()(std::vector<float>&, angle::sharing_angle&);

}