#include "xmlworker.h"
#include <QRegExp>
#include <iostream>
#include <QDebug>
#include <QStringList>



using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// i was disapointed of Qt working with simple xml, so here we'll use regular expressions, sorry,dude :-[////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
XmlWorker::XmlWorker(QObject *parent) : QObject(parent)
{
	content = "";
	qDebug()<<"default coustructor";
}


//initialization constuctor, that opens defined file
XmlWorker::XmlWorker(QFile *file)
{
	content = "";
	bool ret = file->open(QIODevice::ReadOnly | QIODevice::Text);
	if( ret )
	{
		QTextStream stream(file);
		content = stream.readAll();  //here we store whole pseudo-xml text.I know thats sucks;)
	}
	file->close();
	emit contentLoaded(content);
}


QStringList XmlWorker::getElementsByTagName(QString tagName)
{
	QString pattenRegExp = "<"+tagName+">(.*)</"+tagName+">";
	QRegExp rx(pattenRegExp);
	rx.setMinimal(true);   //this f**king directive is necessary!!!!!!!!!!!!
	QStringList list;
	list.clear();
	int pos = 0;
	while ((pos = rx.indexIn(content, pos)) != -1)
	{
		list << rx.cap(1);
		pos += rx.matchedLength();
	}
	return list;
}

QStringList XmlWorker::getElemetsWithArgs(QString tagName, QString tagValue)
{
	QRegExp dateParse;
	QStringList someVar;
	if(tagValue == "")  //here we making avalible to search without tagValue. Just pass "" as second param;)
	{
		dateParse.setPattern("<"+tagName+" value = (\\d\\d\\d\\d-\\d\\d-\\d\\d)>(.*)</"+tagName+">");
	}
	else
	{
		dateParse.setPattern("<"+tagName+" value = ("+tagValue+")>(.*)</"+tagName+">");
	}
	dateParse.setMinimal(true);//and one more VERY IMPORTANT STRING so look up for "VIS" in comments below
	int count = 0;
	int pos = 0;
	while ((pos = dateParse.indexIn(content, pos)) != -1) {
		++count;
		someVar<<dateParse.cap(2);
		pos += dateParse.matchedLength();
	}
	return someVar;
}

QStringList XmlWorker::getValuesByTagName(QString tagName)
{
	QRegExp valueFinder;
	valueFinder.setPattern("<"+tagName+" value = (.*)>");
	QStringList findedValues;
	valueFinder.setMinimal(true);                                             //VIS
	int count = 0;
	int pos = 0;
	while ((pos = valueFinder.indexIn(content, pos)) != -1) {
		++count;
		findedValues<<valueFinder.cap(1);
		pos += valueFinder.matchedLength();
	}
	return findedValues;
}

QStringList XmlWorker::getValuesByTagNameFromString(QString tagName, QString source)
{
	QRegExp valueFinder;
	valueFinder.setPattern("<"+tagName+" value = (.*)>");
	QStringList findedValues;
	valueFinder.setMinimal(true);                                             //VIS
	int count = 0;
	int pos = 0;
	while ((pos = valueFinder.indexIn(source, pos)) != -1) {
		++count;
		findedValues<<valueFinder.cap(1);
		pos += valueFinder.matchedLength();
	}
	return findedValues;
}

QStringList XmlWorker::getElementsFromString(QStringList source, QString tagName)
{
	QRegExp valueFinder;
	valueFinder.setPattern("<"+tagName+" value = \\d\\d:\\d\\d:\\d\\d>(.*)</"+tagName+">"); //here we hardcoded regexp pattern
	QStringList findedValues;                                                               //for time in ISO format
	valueFinder.setMinimal(true);                                             //VIS
	int count = 0;
	int pos = 0;
	while ((pos = valueFinder.indexIn(source[0], pos)) != -1) {
		++count;
		findedValues<<valueFinder.cap(1);
		pos += valueFinder.matchedLength();
	}
	return findedValues;
}

void XmlWorker::appendFirstLevelBlock(QString tagName, QString value)
{
	content.append("\n");
	content.append("\n");
	content.append("<"+tagName+" value = "+value+">");
	content.append("\n");
	content.append("\n");
	content.append("</"+tagName+">");
	qDebug()<<"emited";
	emit contentChanged(content);
}


bool XmlWorker::isBlockExist(QString tagName, QString tagValue)
{
	QRegExp dateParse;
	QStringList someVar;
	dateParse.setPattern("<"+tagName+" value = ("+tagValue+")>(.*)</"+tagName+">");
	dateParse.setMinimal(true);//                                                     VIS
	int count = 0;
	int pos = 0;
	while ((pos = dateParse.indexIn(content, pos)) != -1) {
		++count;
		someVar<<dateParse.cap(1);
		qDebug()<<dateParse.cap(1);
		pos += dateParse.matchedLength();
	}
	if(count != 0)
		return true;
	else
		return false;
}

bool XmlWorker::isBlockEmpty(QString tagName, QString tagValue)
{
	QRegExp dateParse;
	QStringList someVar;
	dateParse.setPattern("<"+tagName+" value = ("+tagValue+")>(.*)</"+tagName+">");
	dateParse.setMinimal(true);//                                                     VIS
	int count = 0;
	int pos = 0;
	while ((pos = dateParse.indexIn(content, pos)) != -1) {
		++count;
		someVar<<dateParse.cap(2);
		qDebug()<<dateParse.cap(2);
		pos += dateParse.matchedLength();
	}
	if(count != 0)
		return true;
	else
		return false;
}
