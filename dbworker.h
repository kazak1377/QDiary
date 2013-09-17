#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql>

class dbworker : public QObject
{
    Q_OBJECT
    QSqlQuery *query;
public:
    explicit dbworker(QObject *parent = 0);
    QSqlDatabase *db;
    dbworker(QString name);
    void addPost(QString date, QString time, QString postText);
    QStringList getDateList();
    QString getPostsByDate(QString date);
signals:

public slots:

};

#endif // DBWORKER_H
