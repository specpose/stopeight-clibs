// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef EDITORINTERFACE_H
#define EDITORINTERFACE_H

#include "listbase.h"

class EditorInterface
{
public:
    //int maxPoints;
     virtual ListBase<dpoint>& getOutput() =0;
     virtual void flushOutput() =0;


     virtual void addPoint(QPointF p) =0;
    // gets called from TileDrawingEvent in inputPress
     virtual void resetLists() =0;
    // gets called on tablet/mouse release
     virtual void automatic() =0;

};


#endif // EDITORINTERFACE_H
