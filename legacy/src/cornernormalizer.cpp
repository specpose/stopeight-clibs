// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "cornernormalizer.h"

template <> void CornerNormalizer<dpoint>::requireMinimumLength(qreal lnt){
    bool foundOne = false;
    for (int i=this->size()-2;i>0;i--){

        if (this->lengthAt(i)<lnt){
            this->removeAt(i);
            foundOne = true;
            break;
        }
    }
    if (foundOne){
        requireMinimumLength(lnt);
    }
}

template<>void CornerNormalizer<dpoint>::intRaster(qreal threshold)
{
	for (int i = 0; i < this->size(); i++) {
		if ( (fmod(this->at(i).x(),1) <=threshold) &&
			 (fmod(this->at(i).y(),1) <= threshold) ) {
			*this << this->at(i);
		}
	}
}


template <> void CornerNormalizer<dpoint>::cornerFilters(){
	// CHECKPRECISION?!
	//debug() << "Before filter corner: ";
    this->smoothingJitter(0);
    CornerNormalizer<dpoint> b = CornerNormalizer<dpoint>(*this);
    b.requireMinimumLength(1.00001);
    ListSwitchable<dpoint> c = ListSwitchable<dpoint>(b);
    c.rotateSegmentToXAxis();
    //this->normalizeCorners();
    //debug() << "After filter corner: ";
}

template<> dpoint CornerNormalizer<dpoint>::getPointInTheMiddle(){
    ListSwitchable<dpoint> myself = ListSwitchable<dpoint>(*this);
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
        ListSwitchable<dpoint> newsection = ListSwitchable<dpoint>();
        newsection << myself.first();
        for (int i=1;i<myself.size();i++){
            newsection<<myself.at(i);
            if (newsection.sumLength()>(myself.sumLength()/2)){
                // get the point1 < position
                dpoint point1 = myself.at(i-1);
                // get the point2 > position
                dpoint point2 = myself.at(i);
                // use middle of two adjacent points
                middle = (point1+point2)/2;
                if (point1.position==-1){
                    if (point2.position==-1){
                        throw std::logic_error("There should not be any inserted points at this stage of the algorithm");
                    } else {
                        p.position = point2.position;
                    }
                    break;
                }
                if (point2.position==-1){
                    if (point1.position==-1){
                        throw std::logic_error("There should not be any inserted points at this stage of the algorithm");
                    } else {
                        p.position = point1.position;
                    }
                    break;
                }
                // set the new position to p1+p2/2
                p.position=point1.position+((point2.position-point1.position)/2);
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
        throw legacy::alg_logic_error("Tried to get middle from 1 point",__FILE__,"");
        return myself.at(0);
    } else {
		throw legacy::alg_logic_error("Tried to get middle from 0 points", __FILE__, "");
    }
}
