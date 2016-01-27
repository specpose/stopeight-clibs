// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cliffsanalyzer.h"

template<> CliffsAnalyzer<dpoint>::CliffsAnalyzer() : CliffsCalculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CliffsAnalyzer<dpoint>::CliffsAnalyzer(F& list) : CliffsCalculator<dpoint>(list){
    // should be listswitchable
    ListBase<dpoint> c = static_cast<ListBase<dpoint>& >(list);
    *this= static_cast<CliffsAnalyzer<dpoint>& >(c);
}

#include "include/areaanalyzer.h"
//area to cliff ok
template CliffsAnalyzer<dpoint>::CliffsAnalyzer(AreaAnalyzer<dpoint>& list);
template CliffsAnalyzer<dpoint>::CliffsAnalyzer(ListCopyable<dpoint>& list);



template <> int CliffsAnalyzer<dpoint>::hasIllegalSegment(){
    ListRotator<dpoint> rotator = ListRotator<dpoint>(*this);
    // has to change to steepest possible?
    rotator.rotateSegmentToXAxis();
    //rotateLastVectorToYAxis();

    for (int i=0;i<rotator.size()-1;i++){
        if ((rotator.at(i+1).rot.x()<=rotator.at(i).rot.x())
                //&&(rotator.at(i+1).rot.y()<HIGHPASS_LOW_LIMIT)
                )
        {
            //debug() << "Illegal Segment found at " << rotator.at(i+1);
            return rotator.at(i+1).position;
        }
    }
    return -1;
}

template<> ListCopyable<dpoint> CliffsAnalyzer<dpoint>::getFirstLegalSegment(){
    CliffsAnalyzer<dpoint> result = CliffsAnalyzer<dpoint>();
    if (this->size()>1){

        bool foundOne=false;
        for (int i=0;i<this->size();i++){
            result<<this->at(i);
            if (result.hasIllegalSegment()!=-1){
                foundOne=true;
                break;
            }
        }
        if (foundOne){
            result.removeLast();
        }
    } else {
        //throw "ListAnalyzer::getFirstLegalSegment: segment size is below 2";
        for (int i=0;i<this->size();i++){
            result<<this->at(i);
        }
    }
    for (int i=0;i<result.size();i++){
        this->removeFirst();
    }

    ////only do this when needed for calculation or display
    // always do this to return valid result
    result.rotateSegmentToXAxis();

    return result;
}
