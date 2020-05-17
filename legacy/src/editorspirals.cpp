// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "editorspirals.h"

//#define debug() QDebug(QtDebugMsg)//::QDebug(QtDebugMsg)
//#define debug() QNoDebug()

EditorSpirals::EditorSpirals() : EditorCliffs()
{
}

//EditorSpirals::~EditorSpirals(){
//    EditorBase::~EditorBase();
//}

//toBeProcessed is modifying data.output
void EditorSpirals::process(ListSwitchable<dpoint> &toBeProcessed){
    // use of output is a hack
    if (this->getOutput().size()>0) {
        /* SHARED CLIFFS&SPIRALS */
        ListSwitchable<dpoint> cliffs;

        /* SPIRALS */
        Spirals<dpoint> spirals = Spirals<dpoint>(toBeProcessed);//Hack from ListBase! //should be move? listswitchable::ListSwitchable(ListBase&&) not working
        cliffs= Spirals<dpoint>::findSpiralCliffs(spirals);

        /* SHARED After this cliffs is const */
        const ListSwitchable<dpoint> constCliffs = cliffs;

        /* SHARED CLIFFS&SPIRALS, But replace cornerMeasuring?? */
        QList<ListSwitchable<dpoint> > slices= QList<ListSwitchable<dpoint> >();
        QList<ListSwitchable<dpoint> >& slicesRef(slices);

        mainIterator(constCliffs,slicesRef);
        const QList<ListSwitchable<dpoint> > constSlices= slices;

        ListSwitchable<dpoint> result = ListSwitchable<dpoint>();

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

ListSwitchable<dpoint> EditorSpirals::processSegment(ListSwitchable<dpoint>::iterator start, ListSwitchable<dpoint>::iterator end){
    return EditorCliffs::processSegment(start,end);
}
