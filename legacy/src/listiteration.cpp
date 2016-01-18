// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/listiteration.h"

template<> ListIteration<dpoint>::ListIteration() : ListBase(){}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> ListIteration<dpoint>::ListIteration(F& list){
    *this = static_cast<ListIteration<dpoint>& >(list);
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void ListIteration<dpoint>::operator=(F& list){
    this->swap(list);
}

template<> ListBase<dpoint> ListIteration<dpoint>::chopCopy(int startPosition, int endPosition){
    ListBase<dpoint> filet;
    for (int i=0;i<this->size();i++){
        if ((this->at(i).position >= startPosition &&
             this->at(i).position <= endPosition) ||
            // this is for reversed pieces, should work...?
            (this->at(i).position <= startPosition &&
             this->at(i).position >= endPosition)
            ){
            filet << this->at(i);
        }
    }
    return filet;
}
