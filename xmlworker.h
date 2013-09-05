#ifndef XMLWORKER_H
#define XMLWORKER_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QStringList>

class XmlWorker : public QObject
{
    Q_OBJECT
    QString content;
public:
    explicit XmlWorker(QObject *parent = 0);
    XmlWorker(QFile *);
    QString genEmptyXml();
    QStringList getElementsByTagName(QString tagName);
    QStringList getElemetsWithArgs(QString tagName, QString tagValue);
    QStringList getValuesByTagName(QString tagName);
    QStringList getValuesByTagNameFromString(QString tagName,QString source);
    QStringList getElementsFromString(QStringList source, QString tagName);
    void appendFirstLevelBlock(QString tagName,QString value);
    void appendSubBlock(QString tagName,QString value,QString parentTag,QString parentValue);
    bool isBlockExist(QString tagName, QString tagValue);
    bool isBlockEmpty(QString tagName,QString tagValue);
signals:
    void contentLoading();
    void contentLoaded(QString);
    void contentChanged(QString);
public slots:
    
};

#endif // XMLWORKER_H
