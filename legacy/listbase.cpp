#include "listbase.h"

#define debug() QDebug(QtDebugMsg)
//#define debug() QNoDebug()

template<> ListBase<dpoint>::ListBase() : QList<dpoint>::QList()
{
    id = 0;
}

// only used for load from file command
// later converted in listanalyzer constructor
/*template<> ListBase<QPointF>::ListBase() : QList<QPointF>::QList()
{
    id = 0;
}*/

template<> ListBase<dpoint> ListBase<dpoint>::loadSPFile(QString& fileName)
//template<typename T> ListAnalyzer<T> ListAnalyzer<T>::loadSPFile(QString& fileName)
{

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        debug()<<"Can't read file "<<file.fileName()<<endl<<file.errorString();
        throw "MainWindow::loadSPFile: Can't read file";
        //return false;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_5);
    unsigned int MagicNumber = 0x8E42B972;
    unsigned int magic;
    in >> magic;
    if (magic != MagicNumber) {
        debug()<<"File is invalid."<<file.fileName()<<endl<<file.errorString();
        throw "MainWindow::loadSPFile: Wrong magic number: "+magic;
        //return false;
    }

    dpoint p;
    ListBase<dpoint> input;
    input.clear();
    while (!in.atEnd()) {
        in >> p;
        input.push_back(p);
    }
    return input;
}
