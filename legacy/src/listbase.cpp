#include "include/listbase.h"

//using namespace legacy;

template<> ListBase<dpoint>::ListBase() : QList<dpoint>::QList()
{
}

template<> ListBase<dpoint> ListBase<dpoint>::loadSPFile(const QString& fileName)
{
    debug()<<"legacy::ListBase<dpoint>::loadSPFile "+fileName.toAscii();
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

template<> ListBase<dpoint> ListBase<dpoint>::open(const std::string utf8path){
    const QString& myString = QString::fromStdString(utf8path);
    return ListBase<dpoint>::loadSPFile(myString);
}
