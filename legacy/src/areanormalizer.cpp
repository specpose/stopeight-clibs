// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/areanormalizer.h"

template<> AreaNormalizer<dpoint>::AreaNormalizer() : AreaCalculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> AreaNormalizer<dpoint>::AreaNormalizer(F& list){
    ListInitializer<dpoint> c = static_cast<ListInitializer<dpoint>& >(list);
    *this= static_cast<AreaNormalizer<dpoint>& >(c);
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void AreaNormalizer<dpoint>::operator=(F& list){
    this->swap(list);
}

//hdojo version
template <> void AreaNormalizer<dpoint>::removeInlays(){
    if (this->size()>4){
        for (int i=0;i<this->size()-4;i++) {
            ListInitializer<dpoint> first, second, third;
            first << this->at(0)<< this->at(1)<< this->at(2);first.rotateSegmentToXAxis(); qreal firstValue = first.at(1).rot.y();
            second << this->at(1)<<this->at(2)<<this->at(3);second.rotateSegmentToXAxis(); qreal secondValue = second.at(1).rot.y();
            third << this->at(2)<<this->at(3)<<this->at(4);third.rotateSegmentToXAxis(); qreal thirdValue = third.at(1).rot.y();
            if (firstValue>0 && secondValue<0&&thirdValue<0 ||
                firstValue<0 && secondValue>0&&thirdValue>0) {this->removeAt(1);this->removeInlays();break;}
            else if (secondValue>0 && firstValue<0&&thirdValue<0 ||
                     secondValue<0 && firstValue>0&&thirdValue>0) {this->removeAt(2);this->removeInlays();break;}
            else if (thirdValue>0 && firstValue<0&&secondValue<0 ||
                     thirdValue<0 && firstValue>0&&secondValue>0) {this->removeAt(3);this->removeInlays();break;}
        }
    }
}

template <>void AreaNormalizer<dpoint>::areaFilters(){
    TurnNormalizer<dpoint> a = TurnNormalizer<dpoint>(this);
    a.smoothingJitter(0);
    CornerNormalizer<dpoint> b = CornerNormalizer<dpoint>(a);
    b.requireMinimumLength(9);
    b.rotateSegmentToXAxis();

    //Port: UNUSED
    //this->risingJitter(0);

    *this=AreaNormalizer<dpoint>(b);
    //debug()<<"Before removeInlays: "<<this->size();
    this->removeInlays();
    //debug()<<"After removeInlays: "<<this->size();

}
