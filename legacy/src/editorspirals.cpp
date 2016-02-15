// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/editorspirals.h"

#define debug() QDebug(QtDebugMsg)//::QDebug(QtDebugMsg)
//#define debug() QNoDebug()

EditorSpirals::EditorSpirals() : EditorBase<ListBase<dpoint> >()
{
}

//EditorSpirals::~EditorSpirals(){
//    EditorBase::~EditorBase();
//}

//toBeProcessed is modifying data.output
void EditorSpirals::process(ListBase<dpoint> &toBeProcessed){
    // use of output is a hack
    if (this->getOutput().size()>0) {
        /* SHARED CLIFFS&SPIRALS */
        QList<dpoint> cliffs;

        /* SPIRALS */
        Spirals<dpoint> spirals = Spirals<dpoint>(toBeProcessed);
        cliffs= Spirals<dpoint>::findSpirals(spirals);
        if (cliffs.size()>0){
        if (cliffs.at(0).position!=0) {
            Analyzer<dpoint> rev = Analyzer<dpoint>(cliffs);
            rev.reverse();
        }
        }

        /* SHARED After this cliffs is const */
        const QList<dpoint> constCliffs = cliffs;

        /* SHARED CLIFFS&SPIRALS, But replace cornerMeasuring?? */
        QList<QList<dpoint> > slices= QList<QList<dpoint> >();
        QList<QList<dpoint> >& slicesRef(slices);

        mainIterator(constCliffs,slicesRef);
        const QList<QList<dpoint> > constSlices= slices;

        ListBase<dpoint> result = ListBase<dpoint>();

        /* SPIRALS&CLIFFS check */
        SpiralsAnalyzer<dpoint>::consistencyCheck(constCliffs);

        /* SHARED */
        result = Analyzer<dpoint>::populateTurns(this->getOutput(),constSlices);

        //hack
        this->setOutput(result);
    } else {
        throw "EditorSpirals::process called without any data";
    }
}

QList<dpoint> EditorSpirals::processSegment(QList<dpoint> list){
    ListRotator<dpoint> cliff = ListRotator<dpoint>(list);
    QList<dpoint> path_section = QList<dpoint>();
    if (cliff.size()>1){
        cliff.rotateSegmentToXAxis();
        //debug()<<"removing illegal points because of illegal segments for debug calc.";
        //cliff.removeIllegalPoints();
        //debug()<<"Points "<<cliff.first().position<<" - "<<cliff.last().position;
        //debug()<<"Number of points in Segment: "<<cliff.length();
        //debug()<<"Length of Curve is: "<<cliff.sumLength();
        //cliff.requireMinimumLength(1);
        /*debug()<<"Area of Curve is: "<<cliff.sumOfDxAreasRotY();
        debug()<<"Spiral-Area of Curve is:"<<cliff.measureSpiral();
        //qreal d = cliff.sumOfDx();
        qreal d = cliff.lengthFromStartToEnd();
        //debug()<<"Radius is: "<<d/2<<"; Segment-Radius-Area is: "<<(pow(d/2,2)*(double)M_PIl)/2;
        debug()<<"Radius is: "<<d/2<<"; Segment-Radius-Area is: "<<ListAnalyzer<dpoint>::area(d,MyLimit);

        //debug()<<"Diameter is: "<<d<<"; Segment-Diameter-Circumference is: "<<(d*(double)M_PIl);
        debug()<<"Diameter is: "<<d<<"; Segment-Diameter-Circumference is: "<<ListAnalyzer<dpoint>::circumference(d,MyLimit);*/

        path_section << cliff.first();
        path_section << cliff.last();
        return path_section;
    } else {
        //throw "ShapeMatcher::cornerMeasuring: this is a humongously small cliff.";
        return path_section;
    }
}
