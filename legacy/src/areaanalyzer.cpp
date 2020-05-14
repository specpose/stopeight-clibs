// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "areaanalyzer.h"

#define debug() QNoDebug()
// Segment-Radius-Area
template<> qreal AreaAnalyzer<dpoint>::area(qreal diameter, qreal base){
    qreal squareOfRadius = pow(diameter/2,2);
    //qreal criteria = (squareOfRadius*(base))/2;
    // accounting for integration error; dangerous when iterating limit
    qreal criteria = (squareOfRadius*(base-M_LOG10El))/2;

    if (criteria<0){throw "AreaCalculator.h::area criteria below zero";}
    return criteria;
}

template<> ListSwitchable<dpoint> AreaAnalyzer<dpoint>::getArea(qreal limit,QPointF start,qreal preceding){
    AreaCalculator<dpoint> result = AreaCalculator<dpoint>();

    bool foundOne=false;

    if (this->size()>1){
        result<<this->first();
        for (int i=1;i<this->size();i++){
            result<<this->at(i);

            result.rotateSegmentToXAxis();

            qreal currentArea = 0;
            if (preceding>0){
                // calculate current triangle based on iteration
                // we need area starting point for this!
                // currentArea += triangle
                currentArea += triangleArea(start,result.first(),result.last());
            }
            // instead of this we could be using an implementation that sums up doubleTriangles
            currentArea += result.sumOfDxAreasRotY();

            if (preceding<0){throw "ListAnalyzer::getArea: preceding is below zero";}
            if (currentArea<0){throw "ListAnalyzer::getArea: currentArea is below zero";}

            // IF preceding + currentArea >= norm: norm is area(fullDIAMETER from start, pi or e, 0)

            AreaCalculator<dpoint> StartEnd = AreaCalculator<dpoint>();
            StartEnd << start << result.last();
            qreal diameter = StartEnd.lengthFromStartToEnd();
            // using sumOfDx would require having all preceding legalSegments from start and adding up sums

            qreal norm = area(diameter,limit);//,0);
            if (norm<0){throw "ListAnalyzer::getArea: norm is below zero";}

            //if (currentArea>=criteria){
            if ((preceding+currentArea)>=norm){
                //debug()<<"#"<<result.last().position<<" Area "<<preceding+currentArea<<" is bigger than norm "<<norm;
                foundOne=true;
                break;
            }
        }
        if (foundOne){
            result.removeLast();
        }
    }
    else {
		throw legacy::alg_logic_error("Before area search segment size is below 2",__FILE__,"");
		//C++11
        //throw legacy::alg_logic_error("Before area search segment size is below 2",__FILE__,__func__);
        for (int i=0;i<this->size();i++){
            result<<this->at(i);
        }
    }
    // removing
    for (int i=0;i<result.size();i++){
        this->removeFirst();
    }

    return result;
}

template<> ListSwitchable<dpoint> AreaAnalyzer<dpoint>::getFirstArea(qreal limit){
    dpoint result = dpoint();
    // needs to be and is a COPY
    ListSwitchable<dpoint> copy = ListSwitchable<dpoint>(*this);
    CliffsAnalyzer<dpoint> calculator = CliffsAnalyzer<dpoint>(copy);

    bool foundOne = false;
    int illegalSegmentCounter=0;

    if (calculator.size()>1){
        ListSwitchable<dpoint> tmp = ListSwitchable<dpoint>(calculator.getFirstLegalSegment());
        AreaAnalyzer<dpoint> legalSegment = AreaAnalyzer<dpoint>(std::move(tmp));
        illegalSegmentCounter++;
        legalSegment.areaFilters();
        tmp = legalSegment.getArea(limit,legalSegment.first());
        AreaAnalyzer<dpoint> preceding = AreaAnalyzer<dpoint>(std::move(tmp));
        if (legalSegment.size()>0){
            foundOne = true;
            result = preceding.last();
        } else {
            qreal sumOfAllPreceding = 0;
            if (calculator.size()>1){
                calculator.prepend(preceding.last());
                tmp = calculator.getFirstLegalSegment();
                legalSegment = AreaAnalyzer<dpoint>(std::move(tmp));
                illegalSegmentCounter++;
                legalSegment.areaFilters();
                preceding.areaFilters();
                tmp = legalSegment.getArea(limit,this->first(),preceding.sumOfDxAreasRotY());
                preceding = AreaAnalyzer<dpoint>(std::move(tmp));
                if (legalSegment.size()>0){
                    foundOne = true;
                    result = preceding.last();
                } else {
                    while (calculator.size()>1){
                        calculator.prepend(preceding.last());
                        tmp = calculator.getFirstLegalSegment();
                        legalSegment = AreaAnalyzer<dpoint>(std::move(tmp));
                        illegalSegmentCounter++;
                        legalSegment.areaFilters();
                        preceding.areaFilters();
                        // sumOfDx over illegal segments is too agressive -> jitter/illegal separation
                        sumOfAllPreceding += preceding.sumOfDxAreasRotY() + preceding.area(preceding.lengthFromStartToEnd(),limit);
                        tmp = legalSegment.getArea(limit,this->first(),sumOfAllPreceding);
                        preceding = AreaAnalyzer<dpoint>(std::move(tmp));
                        if (legalSegment.size()>0){
                            foundOne = true;
                            result = preceding.last();
                            break;
                        }
                    }
                }
            }
        }
    }
    AreaAnalyzer<dpoint> area = AreaAnalyzer<dpoint>();
    if (foundOne){
        //area = util.chopCopy(util.first().position,result.position);
        area.clear();
        auto it = this->position_to_iterator(this->first().position,result.position);
        std::copy(it[0],it[1],std::back_inserter(area));
        //debug()<<"Area has "<<illegalSegmentCounter<<" legal segments.";
    } else {
        area = *this;
    }
    // removing
    for (int i=0;i<area.size();i++){
        this->removeFirst();
    }
    return area;
}

