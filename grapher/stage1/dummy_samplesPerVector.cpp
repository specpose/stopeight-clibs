#include <iostream>
#include <array>
#include <vector>
#include <numeric>
//#include "stopeight-clibs/shared_types.h"
#include "stopeight-clibs/algo_gpx.h"
#include "stopeight-clibs/error.hpp"
template<typename output_t> auto __fixpoint_tester = [](sp::timecode<output_t>& tct_point) {//const
	return (tct_point.category() == sp::FixpointType::FIXPOINT) ? true : false;
};
template<typename output_t> class _sum_blocks2 {
public:
	_sum_blocks2(size_t samplesPerVector) :_samplesPerVector(samplesPerVector) {};//TODO: Align a grid of samplesPerVector to fixPoint
	template<class InputIterator, class OutputIterator> void operator()(const InputIterator begin, const InputIterator end, OutputIterator begin2) {
		if (std::distance(begin, end) < _samplesPerVector)
			throw SFA::util::runtime_error("The requested samplesPerVector size is bigger than the number of input samples", __FILE__, __func__);
		auto number_of_fixpoints = std::count_if(begin, end, __fixpoint_tester<output_t>);
		if (number_of_fixpoints == 0)
			throw SFA::util::runtime_error("This function needs more than zero Fixpoints", __FILE__, __func__);
		else if (number_of_fixpoints > 1)
			throw SFA::util::runtime_error("This function can not work with more than one Fixpoint", __FILE__, __func__);
		auto index_it = std::find_if(begin, end, __fixpoint_tester<output_t>);
		InputIterator new_end = end;
		InputIterator new_beginning = begin;
		//The overhanging bits on either side are hacked of
		if (std::distance(begin, end) > 3 * _samplesPerVector) {//wing test
			//End should always point to the element after the last
			if (std::distance(index_it, end - 1) < _samplesPerVector) {//shift right
				new_beginning += std::distance(begin, end) % _samplesPerVector;
			} else if (std::distance(begin, index_it) < _samplesPerVector) {//shift left
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
		if (int(std::distance(new_beginning, new_end) / _samplesPerVector) % 2 == 0)//floor
			throw SFA::util::runtime_error("The requested samplesPerVector and/or Fixpoint would result in a VectorGraph with an even number of vectors", __FILE__, __func__);
		//The middle ones get promoted
		//for each _samplesPerVectors from the front:
		struct Promoter { std::array<InputIterator, 2> bounds{}; bool isFixpoint = false; };
		std::vector<Promoter> promotableBounds{};
		//1. Create the bounds
		for (int i = 0; i < std::distance(begin, end); i++) {
			for (int j = 0; j < std::distance(begin, end) / _samplesPerVector; j++) {
				Promoter section{};
				std::get<0>(section.bounds) = begin + _samplesPerVector * j;
				std::get<1>(section.bounds) = begin + _samplesPerVector * (j+1);
				section.isFixpoint = false;
			}
		}
		//2. Extract the Fixpoint
		std::for_each(std::begin(promotableBounds), std::end(promotableBounds), [](auto& section) { 
			for (int i = 0; i < std::distance(std::get<0>(section.bounds), std::get<1>(section.bounds)); i++)
				(std::get<0>(section.bounds) + i)->category() ? section.isFixpoint = true : section.isFixpoint = false;
			});
		//3. Sum them up in sequence and append to begin2
		std::transform(std::begin(promotableBounds), std::end(promotableBounds), begin2, [](const Promoter& section) {
			auto blocksum = std::accumulate(std::get<0>(section.bounds), std::get<1>(section.bounds), sp::timecode<output_t>{}, std::plus<sp::timecode<output_t>>{});
			if (section.isFixpoint)
				blocksum.set_category(sp::FixpointType::FIXPOINT);
			return blocksum;
			});
		//4. Promote the Fixpoint
	};
private:
	size_t _samplesPerVector = 1;
};
int main(){
	const size_t samplesPerVector = 2;
	std::array<int16_t,8> samples{0, 1, 2, 3, 4, 5, 6, 7};//3*2+2
	//const size_t samplesPerVector = 3;
	//std::array<int16_t,12> samples{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};//3*3+3
	std::vector<size_t> _fixPoint_indices(1, 0);//default: grapher is ((samples.size() / 2) - 1)
	std::vector<int16_t> differences(samples.size());
	std::adjacent_difference(std::begin(samples), std::end(samples), std::begin(differences));
	auto tc = sp::timecode<int16_t>{};
	//tc.__init({ int16_t(1),int16_t(0) });
	tc.set_x(1);//HACKED?
	tc.set_y(0);
	auto vectors = std::vector<sp::timecode<int16_t>>(differences.size()-1);
	auto func = grapher::_fixpoints(_fixPoint_indices);
	func(std::begin(vectors), std::end(vectors));
	auto index_it = std::find_if(std::begin(vectors), std::end(vectors), __fixpoint_tester<int16_t>);
	auto index = std::distance(std::begin(vectors), index_it);
	std::cout << "The fixpoint index is " << index << std::endl;
	std::vector<sp::timecode<int16_t>> blocks{};
	_sum_blocks2<int16_t> func2(samplesPerVector);
	func2(std::begin(vectors), std::end(vectors), std::back_insert_iterator(blocks));
}