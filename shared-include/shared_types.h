//#pragma once
#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H
namespace sp {
	using element = std::pair<double, double>;
	using result = std::pair<std::vector<element>, std::vector<element>>;
	//using result = std::vector<element>;
	int static _angle(double a, double b) { return 300 * asin(b - a); };
}
sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };

#endif