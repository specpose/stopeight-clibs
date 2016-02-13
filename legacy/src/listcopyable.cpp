// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/listcopyable.h"

#define debug() QNoDebug()


template<> ListCopyable<dpoint>::ListCopyable() : ListBase<dpoint>(),calls(0) {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> ListCopyable<dpoint>::ListCopyable(F& list): ListBase<dpoint>(list), calls(0){
    ListBase<dpoint> c = static_cast<ListBase<dpoint>& >(list);
    *this = static_cast<ListCopyable<dpoint>& >(c);
    //*this = static_cast<ListCopyable<dpoint>& >(list);
}
//template<>template<typename F> ListCopyable<dpoint>::ListCopyable(const F list): ListBase<dpoint>(list), calls(0){
//    *this = list;
//}
// Note: We only make a copy if it's been casted
template<>template<> ListCopyable<dpoint>::ListCopyable(ListCopyable<dpoint>& list) :ListBase<dpoint>(list), calls(0){
    debug()<<"ListCopyable::ListCopyable assignment"<<list.size();

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
template ListCopyable<dpoint>::ListCopyable(AreaCalculator<dpoint>& list);
template ListCopyable<dpoint>::ListCopyable(CliffsAnalyzer<dpoint>& list);
#include "include/cliffs.h"
template ListCopyable<dpoint>::ListCopyable(Cliffs<dpoint>& list);
#include "include/straightsanalyzer.h"
template ListCopyable<dpoint>::ListCopyable(StraightsAnalyzer<dpoint>& list);
#include "include/turnanalyzer.h"
template ListCopyable<dpoint>::ListCopyable(TurnAnalyzer<dpoint>& list);
template ListCopyable<dpoint>::ListCopyable(QList<dpoint>& list);

// the crime scene: needs to know who's called
//template<> ListSwitchable<dpoint>* ListCopyable<dpoint>::operator&(){
//    calls++;
//    debug()<<"Aaargh ListCopyable retrieved";
//}

template<> ListCopyable<dpoint> ListCopyable<dpoint>::chopCopy(int startPosition, int endPosition){
    ListCopyable<dpoint> filet = ListCopyable<dpoint>();
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

template <> void ListCopyable<dpoint>::reverse(){
    ListCopyable<dpoint> reversed= ListCopyable<dpoint>();
    for (int i=this->size()-1;i>=0;i--){
        reversed << this->at(i);
    }
    this->clear();
    this->append(reversed);
}

template <> void ListCopyable<dpoint>::removeIllegalPoints(){
    debug() << "Before removeIllegalPoints: " <<this->size();
    CliffsAnalyzer<dpoint> cliff = CliffsAnalyzer<dpoint>(*this);
    while (cliff.hasIllegalSegment()!=-1){
        for (int i=0;i<cliff.size();i++){
            if (cliff.at(i).position == cliff.hasIllegalSegment()){
                //debug() << "removeIllegalPoints: "<<"Removed point "<<this->at(i)<<".";
                cliff.removeAt(i);
                break;
            }
        }
    }
    debug() << "After removeIllegalPoints: " <<this->size();
}
