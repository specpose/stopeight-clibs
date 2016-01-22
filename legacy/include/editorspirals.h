// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef SPIRALS_H
#define SPIRALS_H

#include "editorbase.h"
#include "spirals.h"
#include "spiralsanalyzer.h"

class EditorSpirals : public EditorBase
{
public:
    EditorSpirals();
    //~EditorSpirals();

protected:
    // automatic detection of "spirals" that don't include any illegal segments, which would make derivations invalid.
    void process(ListBase<dpoint> toBeProcessed);

private:
    static QList<dpoint> processSegment(QList<dpoint> list);
};

#endif // SPIRALS_H
