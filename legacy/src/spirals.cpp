// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/spirals.h"

#define MAX_POINTS 5
//#define LIMIT_TEST M_El
//#define LIMIT_TEST M_PIl
#define LIMIT_ITERATION_STEP 0.1

template<> Spirals<dpoint>::Spirals() : ListInitializer<dpoint>() {}

// Note: typename F can be any implementation of ListBase WITHOUT data members
template<>template<typename F> Spirals<dpoint>::Spirals(F& list){
    ListInitializer<dpoint> c = static_cast<ListInitializer<dpoint>& >(list);
    *this= static_cast<Spirals<dpoint>& >(c);
    //Spirals<dpoint>& test = dynamic_cast<Spirals<dpoint>& >(list);
    //*this = test;
}

template<> QList<dpoint> Spirals<dpoint>::findAreas(ListBase<dpoint> &stroke, qreal limit){
    AreaAnalyzer<dpoint> spiral = AreaAnalyzer<dpoint>(stroke);

    QList<dpoint> result=QList<dpoint>();

    while (spiral.size()>2){
        //    debug()<<"STROKESIZE: "<<stroke.size();
        //if (stroke.size()>2){
        ListBase<dpoint> area = spiral.getFirstArea(limit);
        if (area.size()>0){
            //result << areas;
            result << area.last();
        }
        //debug()<<"Area found: "<<area.last().position<<"remaining stroke size: "<<stroke.size();
    }
    //result<<stroke.last();

    // The very last one is the end of the stroke
    if (result.size()>0){
        result.removeLast();
    }
    return result;
}

template<> qreal Spirals<dpoint>::findLimit(ListBase<dpoint> toBeProcessed){
    QList<dpoint> cliffs;
    qreal MyLimit;
    //Old working:
    //MyLimit = M_El;
    MyLimit = M_PIl;
    //MyLimit = (M_El+M_PIl)/2;
    //MyLimit = 3.135;
    //MyLimit=2*M_PIl/M_El;
    //MyLimit=M_PIl/2;

    // other block:
    //MyLimit=M_PIl/2;
    //MyLimit=0.66666666666666666666666666666666666666666666666666666666666666666666666666 * M_PIl;
    //MyLimit=2*M_PIl/M_El;
    //MyLimit = M_El;

    //throw "ShapeMatcher::process: invalid MyLimit";

    debug()<<"******************* findAreas **********************";
    cliffs=findAreas(toBeProcessed,MyLimit);
    cliffs.size();
    //debug()<<"**************";
    //debug()<<"Found "<<cliffs.size()<<" number of cliffs.";
    //debug()<<"**************";
    if (cliffs.size()>0){
            debug()<<"Found "<<cliffs.size()<<"cliffs, adjusting limit to current minimum";
            int selector=cliffs.size();
            QList<dpoint> backup;
            qreal backupLimit;
            while (cliffs.size()==(selector)){
                backupLimit = MyLimit;
                backup=cliffs;
                MyLimit -= LIMIT_ITERATION_STEP;
                debug()<<"******************* findAreas **********************";
                cliffs=findAreas(toBeProcessed,MyLimit);
            }
            MyLimit=backupLimit;
            cliffs=backup;

    }
    //debug()<<"**************";
    //debug()<<"After adjusting "<<cliffs.size()<<" number of cliffs.";
    //debug()<<"**************";
    //if ( (cliffs.size()!=0) && (fmod(cliffs.size(),2) == 0)){
    //    throw "ShapeMatcher::verify: Inconsistency: even number of cliffs not allowed";
    //}
    debug() << "Found " << cliffs.size() << " cliffs in data.";
    return MyLimit;
}

template<> QList<dpoint> Spirals<dpoint>::findSpirals(ListBase<dpoint> toBeProcessed, bool& pleaseReverse){
    ListBase<dpoint> forward = toBeProcessed;
    //qreal frontSpiral= toBeProcessed.measureSpiral();
    //debug()<<"Forward Spiral Size is: "<<frontSpiral;
    qreal limit = findLimit(toBeProcessed);
    debug()<<"Limit from forward analysis is: "<<limit;

    Analyzer<dpoint> reversed = toBeProcessed;
    //reversed.tripletFilters();
    reversed.reverseOrder();
    //qreal backSpiral= reversed.measureSpiral();
    //debug()<<"Backward Spiral Size is: "<<backSpiral;
    qreal backLimit = findLimit(reversed);
    debug()<<"Limit from backward analysis is: "<<backLimit;
    //if (static_cast<int>(frontSpiral)!=static_cast<int>(backSpiral)){
        //throw "ShapeMatcher::process: spiral-size front/back not equal";
    //}

    QList<dpoint> cliffs=QList<dpoint>();
    if (limit!=backLimit){
        debug()<< "ShapeMatcher::process: different limits found, using larger";
        if (backLimit>limit){
            debug()<<"******************* findAreas::Main **********************";
            cliffs = findAreas(reversed,backLimit);
            pleaseReverse = true;
            //this->data.output.reverseOrder();
        } else {
            debug()<<"******************* findAreas::Main **********************";
            cliffs = findAreas(forward,limit);
        }
    } else {
        debug()<<"******************* findAreas::Main **********************";
        cliffs = findAreas(forward,limit);
    }
    return cliffs;
}

