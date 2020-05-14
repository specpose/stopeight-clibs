// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "areanormalizer.h"
//hdojo version
template <> void AreaNormalizer<dpoint>::removeInlays(){
    if (this->size()>4){
        for (int i=0;i<this->size()-4;i++) {
            ListSwitchable<dpoint> first, second, third;
            first << this->at(0)<< this->at(1)<< this->at(2);first.rotateSegmentToXAxis(); qreal firstValue = first.at(1).rot.y();
            second << this->at(1)<<this->at(2)<<this->at(3);second.rotateSegmentToXAxis(); qreal secondValue = second.at(1).rot.y();
            third << this->at(2)<<this->at(3)<<this->at(4);third.rotateSegmentToXAxis(); qreal thirdValue = third.at(1).rot.y();
            if ((firstValue>0 && secondValue<0&&thirdValue<0) ||
                (firstValue<0 && secondValue>0&&thirdValue>0)) {this->removeAt(1);this->removeInlays();break;}
            else if ((secondValue>0 && firstValue<0&&thirdValue<0) ||
                     (secondValue<0 && firstValue>0&&thirdValue>0)) {this->removeAt(2);this->removeInlays();break;}
            else if ((thirdValue>0 && firstValue<0&&secondValue<0) ||
                     (thirdValue<0 && firstValue>0&&secondValue>0)) {this->removeAt(3);this->removeInlays();break;}
        }
    }
}

template <>void AreaNormalizer<dpoint>::areaFilters(){
	if (this->checkPrecision()) {
		//START OLD
		//this->smoothingJitter(0);
		//this->risingJitter(0);
		//END OLD


		CornerNormalizer<dpoint> zero = CornerNormalizer<dpoint>(std::move(*this));
		zero.requireMinimumLength(5);

		//from linux wacom only:
		//smoothing0
		//rising0
		//removeinlays
		//

		zero.risingJitter(0);
		//a.smoothingJitter(0);
		zero.risingJitter(0);

		//

		CornerNormalizer<dpoint> b = CornerNormalizer<dpoint>(std::move(zero));
		//from below
		b.requireMinimumLength(7);
		//
		b.rotateSegmentToXAxis();
		*this = AreaNormalizer<dpoint>(std::move(b));
		this->removeInlays();
	}
	//if (this->checkPrecision()) {
	//	CornerNormalizer<dpoint> a = CornerNormalizer<dpoint>(*this);
	//	a.intRaster(0.2);
	//	*this = AreaNormalizer<dpoint>(a);
	//}
	else {
		this->smoothingJitter(0);
		CornerNormalizer<dpoint> b = CornerNormalizer<dpoint>(*this);
		b.requireMinimumLength(9);
		b.rotateSegmentToXAxis();

		//Port: UNUSED
		//this->risingJitter(0);

		*this = AreaNormalizer<dpoint>(std::move(b));
		this->removeInlays();
	}

}
