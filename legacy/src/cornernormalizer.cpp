// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cornernormalizer.h"

template<> CornerNormalizer<dpoint>::CornerNormalizer() : CornerCalculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CornerNormalizer<dpoint>::CornerNormalizer(F& list) : CornerCalculator<dpoint>(list){
    ListBase<dpoint> c = static_cast<ListBase<dpoint>& >(list);
    *this= static_cast<CornerNormalizer<dpoint>& >(c);
}

template CornerNormalizer<dpoint>::CornerNormalizer(ListBase<dpoint>& list);
#include "include/areanormalizer.h"
template CornerNormalizer<dpoint>::CornerNormalizer(TurnNormalizer<dpoint>& list);
#include "include/cliffsnormalizer.h"
template CornerNormalizer<dpoint>::CornerNormalizer(CliffsNormalizer<dpoint>& list);
#include "include/listcopyable.h"
template CornerNormalizer<dpoint>::CornerNormalizer(ListCopyable<dpoint>& list);
template CornerNormalizer<dpoint>::CornerNormalizer(AreaNormalizer<dpoint>& list);
template CornerNormalizer<dpoint>::CornerNormalizer(CornerNormalizer<dpoint>& list);

template <> void CornerNormalizer<dpoint>::requireMinimumLength(qreal lnt){
    bool foundOne = false;
    Calculator<dpoint> calc = Calculator<dpoint>(*this);
    for (int i=calc.size()-2;i>0;i--){

        if (calc.lengthAt(i)<lnt){
            calc.removeAt(i);
            foundOne = true;
            break;
        }
    }
    *this=CornerNormalizer<dpoint>(calc);
    if (foundOne){
        requireMinimumLength(lnt);
    }
}


template <> void CornerNormalizer<dpoint>::cornerFilters(){
	// CHECKPRECISION?!
	//debug() << "Before filter corner: ";
    TurnNormalizer<dpoint> a = TurnNormalizer<dpoint>(*this);
    a.smoothingJitter(0);
    CornerNormalizer<dpoint> b = CornerNormalizer<dpoint>(a);
    b.requireMinimumLength(1.00001);
    ListRotator<dpoint> c = ListRotator<dpoint>(b);
    c.rotateSegmentToXAxis();
    //this->normalizeCorners();
    //debug() << "After filter corner: ";
}

template<> dpoint CornerNormalizer<dpoint>::getPointInTheMiddle(){
    StraightsCalculator<dpoint> myself = StraightsCalculator<dpoint>(*this);
    if (myself.size()>2){
        QPointF middle;

        // It is a straight line!
        //draw corner or turn in middle
        // use middle of start and end
        //middle = (myself.last()+myself.first())/2;

        dpoint p = dpoint();
        // this point does not have a position!!
        // -> create one
        // get the length of section
        // find position of adjacent to half length
        StraightsCalculator<dpoint> newsection = StraightsCalculator<dpoint>();
        newsection << myself.first();
        for (int i=1;i<myself.size();i++){
            newsection<<myself.at(i);
            if (newsection.sumLength()>(myself.sumLength()/2)){
                // get the point1 < position
                dpoint point1 = myself.at(i-1);
                // get the point2 > position
                dpoint point2 = myself.at(i);
                // set the new position to p1+p2/2
                p.position=point1.position+((point2.position-point1.position)/2);
                // use middle of two adjacent points
                middle = (point1+point2)/2;
                break;
            }
        }
        p.setX(middle.x());
        p.setY(middle.y());
        return p;
    } else if (myself.size()==2){
        //special case that might happen with integrating triplets from start/reverse
        if (myself.at(0).position==myself.at(1).position){
            return myself.at(0);
        } else {
            dpoint middle = dpoint();
            middle.setX((myself.at(0).x()+myself.at(1).x())/2);
            middle.setY((myself.at(0).y()+myself.at(1).y())/2);
            // setting the new index to half, got better solution?
            middle.position=myself.at(0).position+((myself.at(1).position-myself.at(0).position)/2);
            return middle;
        }
    }else if (myself.size()==1) {
        //throw "CornerNormalizer<dpoint>::getPointInTheMiddle: Tried to get middle from 1 point?";
        return myself.at(0);
    } else {
        throw "CornerNormalizer<dpoint>::getPointInTheMiddle: Size is "+myself.size();
    }
}
