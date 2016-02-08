// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef EDITORSPIRALS_H
#define EDITORSPIRALS_H

#include "editorbase.h"
#include "spirals.h"
#include "spiralsanalyzer.h"

class EditorSpirals : public EditorBase<ListBase<dpoint> >
{
public:
    EditorSpirals();
    //~EditorSpirals();


protected:
    // automatic detection of "spirals" that don't include any illegal segments, which would make derivations invalid.
    void process(ListBase<dpoint>& toBeProcessed);

private:
    QList<dpoint> processSegment(QList<dpoint> list);

};

#endif // EDITORSPIRALS_H
