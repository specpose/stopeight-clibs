// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "cliffs.h"

//#define debug() QDebug(QtDebugMsg)//::QDebug(QtDebugMsg)
#define debug() QNoDebug()

//ShapeMatcher::findCliffs
template<> ListSwitchable<dpoint> Cliffs<dpoint>::findCliffs(ListSwitchable<dpoint> toBeProcessed){
    //test for illegalPointRemoval
    ListSwitchable<dpoint> result=ListSwitchable<dpoint>();
    CliffsAnalyzer<dpoint> calculator = CliffsAnalyzer<dpoint>(toBeProcessed);
    while (calculator.size()>2) {
        calculator.cliffFilters();
        //older
        ListSwitchable<dpoint> cliff = ListSwitchable<dpoint>(calculator.getFirstLegalSegment());
        //or newer impl?
        //ListCopyable<dpoint> cliff = calculator.getFirstCliff();
        result << cliff.last();
    }
    // The last one is the end of the stroke
    result.removeLast();
    return result;
}
