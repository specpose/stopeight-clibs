// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cliffscalculator.h"

template<> CliffsCalculator<dpoint>::CliffsCalculator() : ListSwitchable<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CliffsCalculator<dpoint>::CliffsCalculator(F& list) : ListSwitchable<dpoint>(list){
    // should be listswitchable
    ListBase<dpoint> c = static_cast<ListBase<dpoint>& >(list);
    *this= static_cast<CliffsCalculator<dpoint>& >(c);
}

#include "include/areaanalyzer.h"
template CliffsCalculator<dpoint>::CliffsCalculator(AreaAnalyzer<dpoint>& list);
template CliffsCalculator<dpoint>::CliffsCalculator(ListCopyable<dpoint>& list);

