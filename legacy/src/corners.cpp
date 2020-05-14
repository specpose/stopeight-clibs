// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "corners.h"

#define debug() QNoDebug()

//ShapeMatcher::findCorners
template<> QList<dpoint> Corners<dpoint>::findCorners(ListSwitchable<dpoint> toBeProcessed){
    QList<dpoint> result = QList<dpoint>();

    CornerAnalyzer<dpoint> crest = CornerAnalyzer<dpoint>(toBeProcessed);
    // do this once and don't do it anymore for the rest of the journey: rotation inside
    crest.cornerFilters();

    while (crest.size()>0){
        ListSwitchable<dpoint> corner = crest.getFirstCorner();
        result<<corner.last();
    }
    // The last one is the end of the crest
    result.removeLast();
    //debug()<<"ShapeMatcher::findCorners: detected "<<result.size()<<" corners in algorithm.";
    return result;
}
