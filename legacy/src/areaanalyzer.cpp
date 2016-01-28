// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/areaanalyzer.h"

template<> AreaAnalyzer<dpoint>::AreaAnalyzer() : AreaNormalizer<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> AreaAnalyzer<dpoint>::AreaAnalyzer(F& list) : AreaNormalizer<dpoint>(list) {
    ListBase<dpoint> c = static_cast<ListBase<dpoint>& >(list);
    // ListBase to AreaAnalyzer NOT ok
    *this= static_cast<AreaAnalyzer<dpoint>& >(c);
}

template AreaAnalyzer<dpoint>::AreaAnalyzer(AreaAnalyzer<dpoint>& list);
// listbase to AreaAnalyzer NOT ok
template AreaAnalyzer<dpoint>::AreaAnalyzer(ListBase<dpoint>& list);
template AreaAnalyzer<dpoint>::AreaAnalyzer(ListCopyable<dpoint>& list);

// Segment-Radius-Area
template<> qreal AreaAnalyzer<dpoint>::area(qreal diameter, qreal base){
    qreal squareOfRadius = pow(diameter/2,2);
    //qreal criteria = (squareOfRadius*(base))/2;
    // accounting for integration error; dangerous when iterating limit
    qreal criteria = (squareOfRadius*(base-M_LOG10El))/2;

    if (criteria<0){throw "AreaCalculator.h::area criteria below zero";}
    return criteria;
}

template<> ListCopyable<dpoint> AreaAnalyzer<dpoint>::getArea(qreal limit,QPointF start,qreal preceding){
    AreaCalculator<dpoint> result = AreaCalculator<dpoint>();

    bool foundOne=false;

    if (this->size()>1){
        result<<this->first();
        for (int i=1;i<this->size();i++){
            result<<this->at(i);

            // ABSOLUTELY HAVE TO DO THIS if not preprocessed by getLegalSegment:
            // ALSO Has to be there if calculator chopped / see upstream
            // CORRECTION: ALWAYS NEEDED
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

            // old implementation
            // does not change much:
            //qreal diameter = result.sumOfDx();
            //or:
            //qreal diameter = result.lengthFromStartToEnd();
            //qreal criteria = fabs(ListAnalyzer<dpoint>::area(diameter,limit,preceding));
            //debug()<<"ListAnalyzer::getArea::Criteria is: "<<criteria;

            // IF preceding + currentArea >= norm: norm is area(fullDIAMETER from start, pi or e, 0)

            AreaCalculator<dpoint> StartEnd = AreaCalculator<dpoint>();
            StartEnd << start << result.last();
            qreal diameter = StartEnd.lengthFromStartToEnd();
            // using sumOfDx would require having all preceding legalSegments from start and adding up sums

            qreal norm = area(diameter,limit);//,0);
            //debug()<<"Comparison #"<<i;
            if (norm<0){throw "ListAnalyzer::getArea: norm is below zero";}

            //debug()<<"#"<<result.last().position<<"Area is "<<preceding+currentArea<<" norm is "<<norm;
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
        //throw "ListAnalyzer::getArea: before area search segment size is below 2";
        for (int i=0;i<this->size();i++){
            result<<this->at(i);
        }
    }
    // removing
    for (int i=0;i<result.size();i++){
        this->removeFirst();
    }

    //only do this when needed for calculation or display
    //this->rotateSegmentToXAxis();

    return result;
}

template<> ListBase<dpoint> AreaAnalyzer<dpoint>::getFirstArea(qreal limit){
    dpoint result = dpoint();
    // needs to be and is a COPY
    ListCopyable<dpoint> copy = ListCopyable<dpoint>(*this);
    CliffsAnalyzer<dpoint> calculator = CliffsAnalyzer<dpoint>(copy);
    debug()<<"AreaAnalyzer::getFirstArea after copy this"<<this->size();
    debug()<<"AreaAnalyzer::getFirstArea after copy calculator"<<calculator.size();

    //CliffsAnalyzer<dpoint> calculator = *this;

    bool foundOne = false;
    int illegalSegmentCounter=0;

    if (calculator.size()>1){
        ListCopyable<dpoint> tmp =ListCopyable<dpoint>(calculator.getFirstLegalSegment());
        debug()<<"AreaAnalyzer::getFirstArea after copy getFirstLegalSegment"<<tmp.size();

        AreaAnalyzer<dpoint> legalSegment = AreaAnalyzer<dpoint>(tmp);

        debug()<<"AreaAnalyzer::getFirstArea after cast getFirstLegalSegment"<<legalSegment.size();

        //legalSegment = AreaAnalyzer<dpoint>(calculator.getFirstLegalSegment());
        illegalSegmentCounter++;
        legalSegment.areaFilters();
        tmp = legalSegment.getArea(limit,legalSegment.first());
        AreaAnalyzer<dpoint> preceding = AreaAnalyzer<dpoint>(tmp);
        //debug()<<"ListBase<dpoint>::getFirstArea preceding size: "<<preceding.size();
        if (legalSegment.size()>0){
            foundOne = true;
            result = preceding.last();
        } else {
            qreal sumOfAllPreceding = 0;
            if (calculator.size()>1){
                calculator.prepend(preceding.last());
                tmp = calculator.getFirstLegalSegment();
                legalSegment = AreaAnalyzer<dpoint>(tmp);
                illegalSegmentCounter++;
                legalSegment.areaFilters();
                preceding.areaFilters();
                tmp = legalSegment.getArea(limit,this->first(),preceding.sumOfDxAreasRotY());
                preceding = AreaAnalyzer<dpoint>(tmp);
                if (legalSegment.size()>0){
                    foundOne = true;
                    result = preceding.last();
                } else {
                    while (calculator.size()>1){
                        calculator.prepend(preceding.last());
                        tmp = calculator.getFirstLegalSegment();
                        legalSegment = AreaAnalyzer<dpoint>(tmp);
                        illegalSegmentCounter++;
                        legalSegment.areaFilters();
                        preceding.areaFilters();
                        // sumOfDx over illegal segments is too agressive -> jitter/illegal separation
                        sumOfAllPreceding += preceding.sumOfDxAreasRotY() + preceding.area(preceding.lengthFromStartToEnd(),limit);
                        //sumOfAllPreceding += preceding.sumOfDxAreasRotY() + AreaAnalyzer<dpoint>::area(preceding.lengthFromStartToEnd(),limit);
                        tmp = legalSegment.getArea(limit,this->first(),sumOfAllPreceding);
                        preceding = AreaAnalyzer<dpoint>(tmp);
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
    ListCopyable<dpoint> area = ListCopyable<dpoint>();
    if (foundOne){
        ListCopyable<dpoint> util = ListCopyable<dpoint>(*this);
        area = util.chopCopy(util.first().position,result.position);
        //area = ListBase<dpoint>(util.chopCopy(util.first().position,result.position));
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

