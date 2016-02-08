// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cornercalculator.h"

template<> CornerCalculator<dpoint>::CornerCalculator() : ListSwitchable<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CornerCalculator<dpoint>::CornerCalculator(F& list) : ListSwitchable<dpoint>(list){
    ListSwitchable<dpoint> c = static_cast<ListSwitchable<dpoint>& >(list);
    *this= static_cast<CornerCalculator<dpoint>& >(c);
}

#include "include/turnnormalizer.h"
template CornerCalculator<dpoint>::CornerCalculator(TurnNormalizer<dpoint>& list);
#include "include/calculator.h"
template CornerCalculator<dpoint>::CornerCalculator(Calculator<dpoint>& list);
template CornerCalculator<dpoint>::CornerCalculator(ListBase<dpoint>& list);
#include "include/cliffsnormalizer.h"
template CornerCalculator<dpoint>::CornerCalculator(CliffsNormalizer<dpoint>& list);

