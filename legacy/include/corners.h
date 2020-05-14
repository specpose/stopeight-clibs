// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

//#ifndef CORNERS_H
//#define CORNERS_H

#include "listswitchable.h"
#include "corneranalyzer.h"

template<typename T> class Corners : public ListSwitchable<T>
{
public:
    using ListSwitchable<T>::ListSwitchable;

    // Note: These only work as expected, if crests have been sliced. Otherwise: Only 1st result reliable
    static QList<dpoint> findCorners(ListSwitchable<dpoint> toBeProcessed);

};

//#endif // CORNERS_H
