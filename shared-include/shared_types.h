//#pragma once
#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H
namespace sp {
	/*template<typename T> class fixpoint : timecode<T> {
		fixpoint() {};
		//fixpoint(timecode&& point) :*this{point}
		~fixpoint() override {
			throw std::exception("fixpoints refer to timecode data and can not be deleted.");
		};
	};
	template<typename T> class timecode : public std::pair<T,T> {
	public:
		timecode() {};
		virtual ~timecode() = 0;
	};*/
	using element = std::pair<double, double>;
	using result = std::pair<std::vector<element>, std::vector<element>>;
	//using result = std::vector<element>;
	double static _angle(double diff) { return 300 * asin(diff); };
}
sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };
sp::element static operator-(const sp::element& a, const sp::element& b) { return sp::element{ a.first - b.first, a.second - b.second }; };

#endif