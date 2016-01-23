// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/turnnormalizer.h"

template<> TurnNormalizer<dpoint>::TurnNormalizer() : TurnCalculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> TurnNormalizer<dpoint>::TurnNormalizer(F& list){
    ListInitializer<dpoint> c = static_cast<ListInitializer<dpoint>& >(list);
    *this= static_cast<TurnNormalizer<dpoint>& >(c);
}

#include "include/areanormalizer.h"
template TurnNormalizer<dpoint>::TurnNormalizer(AreaNormalizer<dpoint>& list);


// Note: ALL datamembers of target class destroyed
template<>template<typename F> void TurnNormalizer<dpoint>::operator=(F& list){
    this->swap(list);
}

template <> void TurnNormalizer<dpoint>::smoothingJitter(int pos){
    bool foundOne = false;
    for (int i=pos;i<this->size()-3;i++){
        //if ( (this->sumOfRegressionAt(i) <= 0.5) &&
        if (
             (!this->isRegLineThroughAt(i)) ){
        //if (this->isJitterAt(i) == true) {
            this->removeAt(i+1);
            // danger index change
            this->removeAt(i+1);
            foundOne=true;
            break;
        }
    }
    if (foundOne){
        smoothingJitter(pos+1);
    }
}
