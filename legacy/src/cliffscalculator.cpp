// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cliffscalculator.h"

template<> CliffsCalculator<dpoint>::CliffsCalculator() : ListInitializer<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CliffsCalculator<dpoint>::CliffsCalculator(F& list){
    ListInitializer<dpoint> c = static_cast<ListInitializer<dpoint>& >(list);
    *this= static_cast<CliffsCalculator<dpoint>& >(c);
}
