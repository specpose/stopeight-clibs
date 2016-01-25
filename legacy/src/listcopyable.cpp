// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/listcopyable.h"

template<> ListCopyable<dpoint>::ListCopyable() : ListBase<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> ListCopyable<dpoint>::ListCopyable(F& list){
    ListBase<dpoint> c = static_cast<ListBase<dpoint>& >(list);
    *this = static_cast<ListCopyable<dpoint>& >(c);
    //*this = static_cast<ListCopyable<dpoint>& >(list);
}

// Note: We only make a copy if it's been casted
template<>template<> ListCopyable<dpoint>::ListCopyable(ListCopyable<dpoint>& list){
    *this = list;
}

template ListCopyable<dpoint>::ListCopyable(ListCopyable<dpoint>& list);
template ListCopyable<dpoint>::ListCopyable(ListBase<dpoint>& list);
#include "include/areaanalyzer.h"
template ListCopyable<dpoint>::ListCopyable(AreaAnalyzer<dpoint>& list);
#include "include/spirals.h"
template ListCopyable<dpoint>::ListCopyable(Spirals<dpoint>& list);
#include "include/analyzer.h"
template ListCopyable<dpoint>::ListCopyable(Analyzer<dpoint>& list);

template<> ListBase<dpoint> ListCopyable<dpoint>::chopCopy(int startPosition, int endPosition){
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
