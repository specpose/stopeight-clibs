// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cornernormalizer.h"

template<> CornerNormalizer<dpoint>::CornerNormalizer() : CornerCalculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CornerNormalizer<dpoint>::CornerNormalizer(F& list){
    *this = static_cast<CornerNormalizer<dpoint>& >(list);
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void CornerNormalizer<dpoint>::operator=(F& list){
    this->swap(list);
}

template <> void CornerNormalizer<dpoint>::requireMinimumLength(qreal lnt){
    bool foundOne = false;
    Calculator<dpoint> calc = Calculator<dpoint>(this);
    for (int i=calc.size()-2;i>0;i--){

        if (calc.lengthAt(i)<lnt){
            //debug() << "requireMinimumLength: deleting "<<calc->at(i);
            calc.removeAt(i);
            foundOne = true;
            break;
        }
    }
    *this=calc;
    if (foundOne){
        requireMinimumLength(lnt);
    }
}
