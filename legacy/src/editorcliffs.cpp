// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/editorcliffs.h"

//#define debug() QDebug(QtDebugMsg)//::QDebug(QtDebugMsg)
#define debug() QNoDebug()

EditorCliffs::EditorCliffs() : EditorBase<ListBase<dpoint> >()
{
    debug()<<"EditorCliffs<T>::EditorCliffs() constructor called";
}

//EditorCliffs::~EditorCliffs(){
//    EditorBase::~EditorBase();
//}

//toBeProcessed is modifying data.output
void EditorCliffs::process(ListBase<dpoint> &toBeProcessed){
    debug()<<"EditorCliffs::process reached with data "<<this->getOutput().size();
    // use of output is a hack
    if (this->getOutput().size()>0) {
        /* SHARED CLIFFS&SPIRALS */
        Cliffs<dpoint> data = Cliffs<dpoint>(toBeProcessed);

        QList<dpoint> cliffs= Cliffs<dpoint>::findCliffs(data);

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
        //this->setOutput(this->getOutput().clear());
        this->setOutput(result);//this->data.output.append(result);
    } else {
        throw "EditorCliffs::process called without any data";
    }
}

// this is a drop-in replacement for processSegment used for clarifying math
QList<dpoint> EditorCliffs::processSegment(QList<dpoint> list){
    ListRotator<dpoint> cliff = ListRotator<dpoint>(list);
    QList<dpoint> path_section = QList<dpoint>();
    if (cliff.size()>1){
        cliff.rotateSegmentToXAxis();
        //debug()<<"removing illegal points because of illegal segments for debug calc.";
        //cliff.removeIllegalPoints();
        debug()<<"Points "<<cliff.first().position<<" - "<<cliff.last().position;
        debug()<<"Number of points in Segment: "<<cliff.length();
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
