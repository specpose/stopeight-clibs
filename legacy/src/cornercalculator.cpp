// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cornercalculator.h"

template<> CornerCalculator<dpoint>::CornerCalculator() : ListInitializer<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CornerCalculator<dpoint>::CornerCalculator(F& list){
    *this = static_cast<CornerCalculator<dpoint>& >(list);
}
