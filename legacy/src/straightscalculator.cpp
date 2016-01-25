// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/straightscalculator.h"

template<> StraightsCalculator<dpoint>::StraightsCalculator() : ListSwitchable<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> StraightsCalculator<dpoint>::StraightsCalculator(F& list){
    ListSwitchable<dpoint> c = static_cast<ListSwitchable<dpoint>& >(list);
    *this= static_cast<StraightsCalculator<dpoint>& >(c);
}

#include "include/cornernormalizer.h"
template StraightsCalculator<dpoint>::StraightsCalculator(CornerNormalizer<dpoint>& list);


template <> qreal StraightsCalculator<dpoint>::sumLength(){
    qreal sumLength = 0;
    Calculator<dpoint> calc = Calculator<dpoint>(*this);
    for (int i=0;i<this->size()-1;i++) {
        sumLength += calc.lengthAt(i);
    }
    return sumLength;
}


