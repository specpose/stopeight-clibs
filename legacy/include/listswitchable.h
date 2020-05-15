// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef LISTSWITCHABLE_H
#define LISTSWITCHABLE_H

#define HIGHPASS_LOW_LIMIT 0.0001

#include "turncalculator.h"
//#include <limits>

template<typename T> class ListSwitchable : public TurnCalculator<dpoint>
{
public:
    ListSwitchable<T>(): TurnCalculator<dpoint>() {}
//    template<typename F> ListSwitchable<T>(const F&);
//    template<typename F> ListSwitchable<T>(F&&);
////THIS THING AND ALL INHERITING CAN NOT BE COPIED
//    template<typename F> void operator=(const F& list);
//    template<typename F> void operator=(F&& list);

//Upcast Copy Constructor
template<typename F> ListSwitchable(const F& list) {
    auto copy = F(list);
    *this = static_cast<ListSwitchable<dpoint>&>(copy);
}
//Upcast Move Constructor
template<typename F> ListSwitchable(F&& list) {
    *this = std::move(static_cast<ListSwitchable<dpoint>&&>(list));
}

    void removeAt(int i);

};





#endif // LISTSWITCHABLE_H
