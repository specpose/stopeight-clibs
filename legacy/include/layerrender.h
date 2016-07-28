// Copyright (C) 2009-2015 Specific Purpose Software GmbH

#ifndef LAYERRENDER_H
#define LAYERRENDER_H

#include <QDebug>

//used for vector math
#include <QVector2D>
#include <QLineF>

struct layerrender
{
public:

#if defined(DEBUG) || defined(_DEBUG)
    static QPointF controlFromCorner(QPointF point1, QPointF point2, QPointF point3);
    static QPointF heightedControlFromCorner(QPointF point1, QPointF point2, QPointF point3);
#endif

	static QList<QPointF> quadraticbeziers(QPointF turn1, QPointF corner, QPointF turn2);

private:
#if defined(DEBUG) || defined(_DEBUG)
	static QList<QPointF> constructCubicControlPointsFromControlPoint(QPointF point1, QPointF point2, QPointF point3);
#endif

	static QList<QPointF> constructCubicControlPointsFromCorner(QPointF point1, QPointF point2, QPointF point3);

	static QPointF cornerFromControl(QPointF point1, QPointF point2, QPointF point3);

	static QPointF dividedBase(QPointF point1, QPointF point2, QPointF point3);

    static qreal getAngleOfPoint2(QPointF point1, QPointF point2, QPointF point3);

    static QLineF getSeitenhalbierende(QPointF point1, QPointF point2, QPointF point3);

	//	static bool goneCubic(QPointF point1, QPointF point2, QPointF point3);

	//	static bool isHyperbolic(QPointF point1, QPointF point2, QPointF point3);
};

#endif // LAYERRENDER_H
