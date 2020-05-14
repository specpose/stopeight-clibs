// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "cliffsnormalizer.h"

template <> void CliffsNormalizer<dpoint>::cliffFilters() {
	if (this->checkPrecision()) {
		CornerNormalizer<dpoint> b = CornerNormalizer<dpoint>(*this);
		b.requireMinimumLength(1);
		// enabling this is good for circles, bad for certain spirals, sinus and strokes without enough input data
		b.risingJitter(0);
		//
		b.smoothingJitter(0);
		b.risingJitter(0);
	}
	else {
		CornerNormalizer<dpoint> b = CornerNormalizer<dpoint>(*this);
		b.requireMinimumLength(2);
		//// enabling this is good for circles, bad for certain spirals, sinus and strokes without enough input data
		////toBeProcessed.risingJitter(0);
		b.smoothingJitter(0);
		//c.risingJitter(0);
	}
}
