#include "include/dpoint.h"

dpoint::dpoint() {
    QPointF();
    rot=QPointF();
}

dpoint::dpoint(const QPointF& point){
    dpoint();
    this->setX(point.x());
    this->setY(point.y());
}

QDebug operator<<(QDebug dbg, const dpoint &dp){
    dbg.nospace()
            << "#: " << dp.position <<"; "
            << "x: "<< dp.x() << "; "
            << "y: " << dp.y() << "; "
            << "Rotx: " << dp.rot.x() << "; "
            << "Roty: " << dp.rot.y() << "; ";

    return dbg.space();
}

QDataStream &operator<<(QDataStream &out, const dpoint &dp){
    QPointF p = dp;
    int pos = dp.position;
    out << pos;
    out << p;
    return out;
}

QDataStream &operator>>(QDataStream &in, dpoint &dp){
    QPointF p;
    int pos;
    in >> pos;
    in >> p;
    dp = p;
    dp.position = pos;
    return in;
}
