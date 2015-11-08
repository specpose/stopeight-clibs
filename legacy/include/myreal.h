#ifndef MYREAL_H
#define MYREAL_H

#include <QString>
#include <limits>
#include <cmath>

class MyReal
{
public:
    MyReal(qreal number);
    QString strValue(){
        if (value != value){
            return QString("NaN");
        } else if (value > std::numeric_limits<qreal>::max()){
            return QString("+Inf");
        } else if (value < -std::numeric_limits<qreal>::max()){
            return QString("-Inf");
        } else {
            return QString("");
        }
    }
    bool checkIfValid(){
        QString val = strValue();
        if ( val==QString("NaN") || val==QString("+Inf") || val==QString("-Inf") ){
            return false;
        } else {
            return true;
        }
    }
    bool isInt(){
        if (fmod(value,1) == 0){
            return true;
        }
        return false;
    }
private:
    qreal value;
};

#endif // MYREAL_H
