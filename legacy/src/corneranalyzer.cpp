// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "corneranalyzer.h"

#define debug() QNoDebug()

template <> ListSwitchable<dpoint> CornerAnalyzer<dpoint>::getFirstCorner(){
    Analyzer<dpoint> result = Analyzer<dpoint>();

    // used to be >1
    if (this->size()>3){
        //careful!
        result << this->at(0) << this->at(1) << this->at(2);

        // changed from this to calc
        CliffsCalculator<dpoint> calc = CliffsCalculator<dpoint>(*this);
        for (int i=3;i<calc.size();i++){
            if (calc.deriv1Crossed(i)){
                break;
            }
            result << calc.at(i);
        }

    } else {
        //throw "ListAnalyzer::getFirstCorner: Segment is below 4. too short for detecting corners.";
        for (int i=0;i<this->size();i++){
            result<<this->at(i);
        }
    }

    // removing
    for (int i=0;i<result.size();i++){
        this->removeFirst();
    }

    // don't ever rotate in here!

    return result;
}
