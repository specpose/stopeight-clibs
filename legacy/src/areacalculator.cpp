// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/areacalculator.h"

template<> AreaCalculator<dpoint>::AreaCalculator() : ListRotator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> AreaCalculator<dpoint>::AreaCalculator(F& list){
    *this = static_cast<AreaCalculator<dpoint>& >(list);
}

// Segment-Radius-Area
template<> qreal AreaCalculator<dpoint>::area(qreal diameter, qreal base){
    qreal squareOfRadius = pow(diameter/2,2);
    //qreal criteria = (squareOfRadius*(base))/2;
    // accounting for integration error; dangerous when iterating limit
    qreal criteria = (squareOfRadius*(base-M_LOG10El))/2;

    if (criteria<0){throw "AreaCalculator.h::area criteria below zero";}
    return criteria;
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
