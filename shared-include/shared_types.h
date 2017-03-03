#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H

using element = std::pair<double, double>;
element operator+(const element& a, const element& b) { return element{ a.first + b.first, a.second + b.second }; };

#endif