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
    ListSwitchable<T>();
    template<typename F> ListSwitchable<T>(const F&);
    template<typename F> ListSwitchable<T>(F&&);
    //THIS THING AND ALL INHERITING CAN NOT BE COPIED
    template<typename F> void operator=(const F& list);
    template<typename F> void operator=(F&& list);


    void removeAt(int i);

};





#endif // LISTSWITCHABLE_H
