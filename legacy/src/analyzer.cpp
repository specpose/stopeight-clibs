// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "analyzer.h"

#define debug() QNoDebug()

// Sould only be allowed in ListCopyable
// only call ONCE
template<> void Analyzer<dpoint>::reverseOrder(){
    ListSwitchable<dpoint> reversed= ListSwitchable<dpoint>();
    int pointer = 0;
    for (int i=this->size()-1;i>=0;i--){
        dpoint point = this->at(i);
        point.position=pointer;
        reversed << point;
        pointer++;
    }
    this->clear();
    this->append(reversed);
}

template<> Calculator<dpoint> Analyzer<dpoint>::populateTurns(const ListBase<dpoint>& originalData, const QList<QList<dpoint> > slices){
    Calculator<dpoint> result;
    for (int k=0;k<slices.size();k++){
        for (int l=0;l<slices[k].size()-1;l++){
            result << slices[k][l];
            // this is for debugging turn detection
            //ListBase<dpoint> lst = iter.chopCopy(slices[k][l].position,slices[k][l+1].position);
            ListBase<dpoint>& temp = const_cast<ListBase<dpoint>&>(originalData);
            auto it = temp.position_to_iterator(slices[k][l].position,slices[k][l+1].position);
            auto mid = CornerNormalizer<dpoint>();
            std::copy(it[0],it[1],std::back_inserter(mid));
            auto middle = mid.getPointInTheMiddle();
            middle.position = -1;
            result << middle;
            //result << mid.getPointInTheMiddle();
        }
        if ((k==slices.size()-1) && (slices[k].size()>0)){
            result << slices[k].last();
        }
    }
    return result;
}
