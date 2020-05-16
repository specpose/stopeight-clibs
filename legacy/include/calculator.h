// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "listswitchable.h"


template<typename T> class Calculator : public ListSwitchable<T>
{
public:
    //using ListSwitchable<T>::ListSwitchable;
Calculator<T>() : ListSwitchable<dpoint>() {}
template<typename F> Calculator(const F& list) {
    auto copy = F(list);
    *this = static_cast<Calculator<dpoint>&>(copy);
}
//Upcast Move Constructor
template<typename F> Calculator(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<Calculator<dpoint>>(copy);
}

    // Note: this is simple reversal. it is not checking order. Should be static.
    void reverse();



};

#endif // CALCULATOR_H
