// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/listbase.h"

#define debug() QNoDebug()

//using namespace legacy;

template<> ListBase<dpoint>::ListBase() : QList<dpoint>::QList()
{
}

//template<> ListBase<dpoint>::~ListBase(){}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> ListBase<dpoint>::ListBase(F& list) : QList<dpoint>::QList(list){
    *this = static_cast<ListBase<dpoint>& >(list);
}

template ListBase<dpoint>::ListBase(ListBase<dpoint>& list);
#include "include/spirals.h"
template ListBase<dpoint>::ListBase(Spirals<dpoint>& list);
template ListBase<dpoint>::ListBase(Analyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(AreaAnalyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(CliffsAnalyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(AreaCalculator<dpoint>& list);
template ListBase<dpoint>::ListBase(ListCopyable<dpoint>& list);
template ListBase<dpoint>::ListBase(TurnNormalizer<dpoint>& list);
template ListBase<dpoint>::ListBase(Calculator<dpoint>& list);
template ListBase<dpoint>::ListBase(ListSwitchable<dpoint>& list);
template ListBase<dpoint>::ListBase(QList<dpoint>& list);
template ListBase<dpoint>::ListBase(AreaNormalizer<dpoint>& list);
template ListBase<dpoint>::ListBase(CornerNormalizer<dpoint>& list);
#include "include/cliffs.h"
template ListBase<dpoint>::ListBase(Cliffs<dpoint>& list);
template ListBase<dpoint>::ListBase(CliffsNormalizer<dpoint>& list);
#include "include/turnanalyzer.h"
template ListBase<dpoint>::ListBase(TurnAnalyzer<dpoint>& list);
#include "include/straightsanalyzer.h"
template ListBase<dpoint>::ListBase(StraightsAnalyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(CornerAnalyzer<dpoint>& list);

template<> ListBase<dpoint> ListBase<dpoint>::loadSPFile(const QString& fileName)
{
    debug()<<"legacy::ListBase<dpoint>::loadSPFile "+fileName.toLatin1();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
		throw legacy::alg_logic_error((file.errorString().toStdString()+file.fileName().toStdString()).c_str(),__FILE__,__func__);
		//throw std::string(file.errorString().toStdString() + " reading file " + file.fileName().toStdString());
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

template<> ListBase<dpoint> ListBase<dpoint>::open(const char *fileName){
    const QString& myString = QString::fromLatin1(fileName);
    return ListBase<dpoint>::loadSPFile(myString);
}

//needed for wrapper!
template ListBase<dpoint> ListBase<dpoint>::open(const char *fileName);
