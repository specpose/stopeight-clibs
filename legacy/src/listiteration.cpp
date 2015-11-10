#include "include/listiteration.h"

// Note: typename F can be any implementation of ListBase WITHOUT data members
template<>template<typename F> ListIteration<dpoint>::ListIteration(F& list){
    ListIteration<dpoint>& test = static_cast<ListIteration<dpoint>& >(list);
    *this = test;
}

template<> QList<dpoint> ListIteration<dpoint>::chopCopy(int startPosition, int endPosition){
    QList<dpoint> filet;
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
