// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cliffscalculator.h"

#define ZERO_INCLIN1 0
#define ZERO_INCLIN2 0

template<> CliffsCalculator<dpoint>::CliffsCalculator() : ListSwitchable<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CliffsCalculator<dpoint>::CliffsCalculator(F& list) : ListSwitchable<dpoint>(list){
    // should be listswitchable
    ListBase<dpoint> c = static_cast<ListBase<dpoint>& >(list);
    *this= static_cast<CliffsCalculator<dpoint>& >(c);
}

#include "include/areaanalyzer.h"
template CliffsCalculator<dpoint>::CliffsCalculator(AreaAnalyzer<dpoint>& list);
template CliffsCalculator<dpoint>::CliffsCalculator(ListCopyable<dpoint>& list);
#include "include/corneranalyzer.h"
template CliffsCalculator<dpoint>::CliffsCalculator(CornerAnalyzer<dpoint>& list);

// inline specialisation
template <> QPointF CliffsCalculator<dpoint>::delta1At(int position){

    if (position<this->size()){
        ////if (position<(this->size()+calcTail.size()){
        //this->appendTail();
        ////this->append(calcTail);

        // this has to change to steepest possible
        //this->rotateSegmentToXAxis();
        dpoint point1,point2;
        QPointF delta1;

        QListIterator<dpoint> i(*this);
        if (i.findNext(this->at(position))) {
            if (i.hasPrevious()){
                point1 = i.previous();
                if (i.hasNext()){
                    i.next();
                    if (i.hasNext()){
                        point2 = i.next();
                        delta1 = point2.rot-point1.rot;
                        ////debug()<<"delta1At: "<<delta1<<this->at(position);

                        ////for (int i=0;i<calcTail.size();i++){
                        ////    this->removeLast();
                        ////}
                        //this->removeTail();
                        return delta1;
                    } else {
                        //this->removeTail();
                        return QPointF(0,0);
                    }
                }
            } else {
                //this->removeTail();
                return QPointF(0,0);
            }
        } else {
            //this->removeTail();
            return QPointF(0,0);
        }
    } else {
        throw "ListCalculator<dpoint>::delta1At: index out of range";
        // never happens
        return QPointF(0,0);
    }
    throw "ListCalculator<dpoint>::delta1At";
    // never happens
    return QPointF(0,0);
}

template <> qreal CliffsCalculator<dpoint>::inclin1At(int i){
    QPointF d1 = this->delta1At(i);
    //debug()<<"delta1At.y:"<<d1.y()<<", delta1At.x:"<<d1.x()<<this->at(i);
    //if (d1.x()==0) {
    //    return 0;
    //} else {
    return d1.y()/d1.x();
    //}
}

// Warning: this is looking back
template <> bool CliffsCalculator<dpoint>::deriv1Crossed(int pos){
    if(pos < 1)
        return false;

    qreal d1 = this->inclin1At(pos-1);
    qreal d2 = this->inclin1At(pos);

    // This will get the first corner but might be catching too early: d1=0,d2=0
    if ( (d2>=ZERO_INCLIN1&&d1<=-ZERO_INCLIN1) || (d2<=-ZERO_INCLIN1&&d1>=ZERO_INCLIN1)){
        return true;
    }
    return false;
}
