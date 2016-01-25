// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cliffscalculator.h"

template<> CliffsCalculator<dpoint>::CliffsCalculator() : ListSwitchable<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CliffsCalculator<dpoint>::CliffsCalculator(F& list){
    ListSwitchable<dpoint> c = static_cast<ListSwitchable<dpoint>& >(list);
    *this= static_cast<CliffsCalculator<dpoint>& >(c);
}
