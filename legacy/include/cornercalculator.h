// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CORNERCALCULATOR_H
#define CORNERCALCULATOR_H

#include "listswitchable.h"

template<typename T> class CornerCalculator : public ListSwitchable<T>
{
public:
    //using ListSwitchable<T>::ListSwitchable;
CornerCalculator<T>() : ListSwitchable<T>() {}
CornerCalculator<T>(const CornerCalculator<T>&) = default;
CornerCalculator<T>(CornerCalculator<T>&&) = default;
CornerCalculator<T>& operator=(const CornerCalculator<T>&) = default;
CornerCalculator<T>& operator=(CornerCalculator<T>&&) = default;
template<typename F> CornerCalculator(const F& list) {
    auto copy = F(list);
    *this = static_cast<CornerCalculator<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> CornerCalculator(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<CornerCalculator<T>>(copy);
}
};

#endif // CORNERCALCULATOR_H
