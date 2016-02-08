// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/cliffsanalyzer.h"

template<> CliffsAnalyzer<dpoint>::CliffsAnalyzer() : CliffsNormalizer<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> CliffsAnalyzer<dpoint>::CliffsAnalyzer(F& list) : CliffsNormalizer<dpoint>(list){
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

//NEVER USED
//editorcliffs implementation is using getFirstLegalSegment
//FOR REFERENCE
template<> ListCopyable<dpoint> CliffsAnalyzer<dpoint>::getFirstCliff(qreal limit){
    //specialised internally!
    dpoint result = dpoint();

    //ListAnalyzer<dpoint> calculator = *this;
    // from AreaAnalyzer::getFirstArea
    // needs to be and is a COPY
    ListCopyable<dpoint> copy = ListCopyable<dpoint>(*this);
    CliffsAnalyzer<dpoint> calculator = CliffsAnalyzer<dpoint>(copy);

    bool foundOne = false;

    // Spirals getFirstArea implementation, now areaanalyzer
    /*
    int illegalSegmentCounter=0;

    if (calculator.size()>1){
        ListAnalyzer<dpoint> legalSegment = calculator.getFirstLegalSegment();
        illegalSegmentCounter++;
        legalSegment.areaFilters();
        ListAnalyzer<dpoint> preceding = legalSegment.getArea(limit,legalSegment.first());
        //debug()<<"ListAnalyzer<dpoint>::getFirstArea preceding size: "<<preceding.size();
        if (legalSegment.size()>0){
            foundOne = true;
            result = preceding.last();
        } else {
            qreal sumOfAllPreceding = 0;
            if (calculator.size()>1){
                calculator.prepend(preceding.last());
                legalSegment = calculator.getFirstLegalSegment();
                illegalSegmentCounter++;
                legalSegment.areaFilters();
                preceding.areaFilters();
                preceding = legalSegment.getArea(limit,this->first(),preceding.sumOfDxAreasRotY());
                if (legalSegment.size()>0){
                    foundOne = true;
                    result = preceding.last();
                } else {
                    while (calculator.size()>1){
                        calculator.prepend(preceding.last());
                        legalSegment = calculator.getFirstLegalSegment();
                        illegalSegmentCounter++;
                        legalSegment.areaFilters();
                        preceding.areaFilters();
                        // sumOfDx over illegal segments is too agressive -> jitter/illegal separation
                        sumOfAllPreceding += preceding.sumOfDxAreasRotY() + ListCalculator<dpoint>::area(preceding.lengthFromStartToEnd(),limit);
                        preceding = legalSegment.getArea(limit,this->first(),sumOfAllPreceding);
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

    */

    // directional cliffs implementation?
    // first Operation without preceding triangles and areas
    while (calculator.size()>1){
        ListCopyable<dpoint> legalSegment = calculator.getFirstLegalSegment();//cliffs
        //if (count!=0 && legalSegment.size()>0){
        //    legalSegment.removeFirst();
        //}

        if (calculator.size()>1){
            // + tiny bit in between
            calculator.prepend(legalSegment.last());

            AreaAnalyzer<dpoint> dxAreas = AreaAnalyzer<dpoint>(legalSegment);
            // changed to new format limit, start, limit preceding DOES NOT WORK WITH NEW ALGO
            ListCopyable<dpoint> area = dxAreas.getArea(limit,dxAreas.first());//area
            calculator = CliffsAnalyzer<dpoint>(dxAreas);
            //if (count!=0 && legalSegment.size()>0){
            //    area.removeFirst();
            //}
            if (this->last().position!=area.last().position){
                // + tiny bit in between
                calculator.prepend(area.last());
                foundOne = true;
                result=area.last();
            } else {
                //// BUG:
                ////return this->chopCopy(area.last().position, this->last().position);
                //result = this->last();
                //return result;

                //infinite loop break
                break;
            }
        }
    }
    // never reached
    // BUG: catch for calculator.size above
    result=this->last();

    // SHARED by spirals implementation and directional cliffs implementation
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


    // TCT implementation?
    //------------------------------- Old_implementation --------------------------------------
    // Second Operation with preceding triangle and preceding Area
    //if (calculator.size()>1){
    //  ListAnalyzer<dpoint> legalSegment = calculator.getFirstLegalSegment();
    /*if (legalSegment.size()>1){
            int pos = legalSegment.last().position;

            // +tiny little triangle between precedent and current
            //precedent
            precedent.removeLast();//tiny little triangle duplicate

            // preceding Area
            preceding += precedent.sumOfDxAreasRotY();

            precedent = legalSegment.getArea(limit,preceding);
            if (pos==precedent.last().position){
                // + tiny bit in between
                calculator.prepend(precedent.last());
            } else {
                return this->chopCopy(precedent.last().position, this->last().position);
            }
        }*/
    //debug()<<"**************** legalSegment ******************";
    //debug()<<legalSegment;
    //result<<legalSegment.last();
    //}
    // Third Operation with preceding Area(s) plus one preceding triangle
    /*while (calculator.size()>1){
        ListAnalyzer<dpoint> legalSegment = calculator.getFirstLegalSegment();
        if (legalSegment.size()>1){
            int pos = legalSegment.last().position;

            // +tiny little triangle between precedent and current
            //precedent
            precedent.removeLast();//tiny little triangle duplicate

            // preceding Area
            preceding += precedent.sumOfDxAreasRotY();

            // calculating fixed triangle of preceding operation: only on third operation!
            //precedent.first to precedent.last
            //qreal triangle

            ListAnalyzer<dpoint> precedent = legalSegment.getArea(limit,preceding);
            if (pos==precedent.last().position){
                // + tiny bit in between
                calculator.prepend(precedent.last());
            } else {
                return this->chopCopy(precedent.last().position, this->last().position);
            }
        }
        result<<legalSegment.last();
    }
    return result;*/
}
