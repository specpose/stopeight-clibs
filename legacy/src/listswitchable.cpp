// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "listswitchable.h"

//#define debug() QDebug::QDebug(QtDebugMsg)
//#define debug() QNoDebug()
template<> ListSwitchable<dpoint>::ListSwitchable() : TurnCalculator<dpoint>() {
}
template<>template<typename F> ListSwitchable<dpoint>::ListSwitchable(const F& list) : TurnCalculator<dpoint>(list) {
//    *this = static_cast<ListSwitchable<dpoint>&>(list);
}
template<>template<> ListSwitchable<dpoint>::ListSwitchable(QList<dpoint>& list) {*this = list;}
template<>template<> ListSwitchable<dpoint>::ListSwitchable(ListBase<dpoint>& list) { *this = list; }
//template<>template<> ListSwitchable<dpoint>::ListSwitchable(ListBase<dpoint>&& list) { *this = std::move(list); }
template<>template<typename F> ListSwitchable<dpoint>::ListSwitchable(F&& list) : TurnCalculator<dpoint>{std::move(list)} {
//    *this = std::move(static_cast<ListSwitchable<dpoint>&>(list));
}
//template ListSwitchable<dpoint>::ListSwitchable(ListBase<dpoint>&&);
template ListSwitchable<dpoint>::ListSwitchable(ListSwitchable<dpoint>&);
template ListSwitchable<dpoint>::ListSwitchable(ListSwitchable<dpoint>&&);
#include "cliffsanalyzer.h"
template ListSwitchable<dpoint>::ListSwitchable(CliffsAnalyzer<dpoint>&&);
template ListSwitchable<dpoint>::ListSwitchable(AreaCalculator<dpoint>&&);
#include "areaanalyzer.h"
template ListSwitchable<dpoint>::ListSwitchable(AreaAnalyzer<dpoint>&);
template ListSwitchable<dpoint>::ListSwitchable(AreaAnalyzer<dpoint>&&);
template ListSwitchable<dpoint>::ListSwitchable(AreaNormalizer<dpoint>&);
template ListSwitchable<dpoint>::ListSwitchable(AreaNormalizer<dpoint>&&);
template ListSwitchable<dpoint>::ListSwitchable(CliffsNormalizer<dpoint>&);
template ListSwitchable<dpoint>::ListSwitchable(CornerNormalizer<dpoint>&);
template ListSwitchable<dpoint>::ListSwitchable(CornerNormalizer<dpoint>&&);
#include "corneranalyzer.h"
template ListSwitchable<dpoint>::ListSwitchable(CornerAnalyzer<dpoint>&);
#include "analyzer.h"
template ListSwitchable<dpoint>::ListSwitchable(Analyzer<dpoint>&&);
#include "cliffs.h"
template ListSwitchable<dpoint>::ListSwitchable(Cliffs<dpoint>&);
#include "spirals.h"
template ListSwitchable<dpoint>::ListSwitchable(Spirals<dpoint>&);

template<>template<typename F> void ListSwitchable<dpoint>::operator=(const F& list) {
    this->swap(list);
}
template<>template<typename F> void ListSwitchable<dpoint>::operator=(F&& list) {
   ////REQUIRES PHYSICAL COPY: ERROR MSVC
   ////MEMORY LEAK
   //ListBase<dpoint> copy = ListBase<dpoint>(list);
   //*this = static_cast<ListSwitchable<dpoint>&>(copy);
   ////throw std::runtime_error("ListSwitchable assigned with const");
    *this = std::move(list);
}

template <> void ListSwitchable<dpoint>::removeAt(int i) {
    if (i<0) {
        //debug()<<"Illegal position for point removal: "<<i;
        return;
    }
    if (i>this->size()-1) {
        //debug()<<"Illegal position for point removal: "<<i;
        return;
    }
    if ( (i==0 )|| (i==this->size()-1) ){
        //debug() << "WARNING: deleting first or last point in subsegment, pos: "<< this->at(i).position;
    }
    QList<dpoint>::removeAt(i);
    // watch out, this happens AFTER remove
    if ( (i==0 )|| (i==this->size()) ){
        //this has to change to steepest possible
        rotateSegmentToXAxis();
        //this->rotateLastVectorToYAxis();
    }
}
