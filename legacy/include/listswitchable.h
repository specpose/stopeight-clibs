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
    using TurnCalculator<T>::TurnCalculator;
    //ListSwitchable<T>() = default;
    //ListSwitchable<T>(const ListSwitchable<T>&) = default;
    //ListSwitchable<T>(ListSwitchable<T>&&) = default;
//    template<typename F> ListSwitchable<T>(const F&);
//    template<typename F> ListSwitchable<T>(F&&);
////THIS THING AND ALL INHERITING CAN NOT BE COPIED
//    template<typename F> void operator=(const F& list);
//    template<typename F> void operator=(F&& list);

/*
ListSwitchable<T>(const ListSwitchable&) = default;
ListSwitchable<T>(ListSwitchable&&) = default;
//Upcast Move Constructor
ListSwitchable<T>(const QList<T>& list) {
    auto copy = QList<T>(list);
    *this = static_cast<ListSwitchable<T>&>(copy);
}
//Upcast Move Constructor
ListSwitchable<T>(QList<T>&& list) {
    auto copy = std::move(list);
    *this = static_cast<ListSwitchable<T>>(copy);
}*/

    void removeAt(int i);

};





#endif // LISTSWITCHABLE_H
