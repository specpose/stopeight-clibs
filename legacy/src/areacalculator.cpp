// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/areacalculator.h"

template<> AreaCalculator<dpoint>::AreaCalculator() : ListSwitchable<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> AreaCalculator<dpoint>::AreaCalculator(F& list){
    ListSwitchable<dpoint> c = static_cast<ListSwitchable<dpoint>& >(list);
    *this= static_cast<AreaCalculator<dpoint>& >(c);
}

// this is buggy has to be reworked. inlays are not properly removed by just subtracting them!
template <> qreal AreaCalculator<dpoint>::sumOfDxAreasRotY(){
    qreal sum = 0;
    // Segments don't have calcTails
    if (this->size()>1){
        for (int i = 0;i<this->size()-1;i++){
            if (this->at(i+1).rot.x()>this->at(i).rot.x()){
            qreal piece =
                    //fabs(this->at(i+1).rot.x()-this->at(i).rot.x())
                    (this->at(i+1).rot.x()-this->at(i).rot.x())
                    *
                    //jitter big - needed unless turns detected - results more accurate with seg-rad-area
                    // actually this may not be jitter, but just negative rotation (from start)
                    //fabs(this->at(i).rot.y())
                    this->at(i).rot.y()
                    +
                    (
                            //jitter small
                            //fabs(this->at(i+1).rot.y()-this->at(i).rot.y())
                            (this->at(i+1).rot.y()-this->at(i).rot.y())
                            *
                            //fabs(this->at(i+1).rot.x()-this->at(i).rot.x())
                            (this->at(i+1).rot.x()-this->at(i).rot.x())
                            )/2
                    ;
            if ((sum>0 && piece<0) ||
                (sum<0 && piece>0) )
            {
                //this is jitter! perform turn detection before spiral subsectioning
                debug()<<"sum: "<<sum<<" piece: "<<piece<<" at position "<<this->at(i).position;
                throw "AreaCalculator::sumOfDxAreasRotY: jitter detected. detect turns first and then make ascending/descending";
            } else {
            sum += piece;
            }
        } else {
            throw "AreaCalculator::sumOfDXArea: bug in getFirstLegalSegment";
        }
        }
    }
    return fabs(sum);
}

template <> qreal AreaCalculator<dpoint>::lengthFromStartToEnd(){
    dpoint start = this->first();
    dpoint end = this->last();
    return Calculator<dpoint>::lengthOf(end-start);
}

template <> qreal AreaCalculator<dpoint>::triangleArea(QPointF A, QPointF B, QPointF C)
{
    AreaCalculator<dpoint> a = AreaCalculator<dpoint>();
    a << C << B;
    AreaCalculator<dpoint> b = AreaCalculator<dpoint>();
    b << A << C;
    AreaCalculator<dpoint> c = AreaCalculator<dpoint>();
    c << A << B;
    qreal s = ((a.lengthFromStartToEnd())+(b.lengthFromStartToEnd())+(c.lengthFromStartToEnd()))/2;
    qreal Area = sqrt( s * (s-a.lengthFromStartToEnd()) * (s-b.lengthFromStartToEnd()) * (s-c.lengthFromStartToEnd()) );
    if (Area<0){throw "AreaCalculator::triangleArea: is below zero";}

    return Area;
}
