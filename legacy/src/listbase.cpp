// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/listbase.h"

//using namespace legacy;

template<> ListBase<dpoint>::ListBase() : QList<dpoint>::QList()
{
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> ListBase<dpoint>::ListBase(F& list){
    *this = static_cast<ListBase<dpoint>& >(list);
}

template ListBase<dpoint>::ListBase(ListBase<dpoint>& list);
#include "include/spirals.h"
template ListBase<dpoint>::ListBase(Spirals<dpoint>& list);
template ListBase<dpoint>::ListBase(Analyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(CliffsAnalyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(AreaCalculator<dpoint>& list);

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void ListBase<dpoint>::operator=(F& list){
    // does this use =
    //this->QList(list);
    // this does
    //this->ListBase(F)
    // this is not supposed to
    this->swap(list);
}

#include "include/areaanalyzer.h"
template void ListBase<dpoint>::operator=(AreaAnalyzer<dpoint>& list);

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
