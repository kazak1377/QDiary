#include "dbworker.h"
#include <QtSql>

dbworker::dbworker(QObject *parent) : QObject(parent)
{
}

dbworker::dbworker(QString name)
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(name);
    if (!db->open())
    {
        qDebug() << db->lastError().text();
    }
    //add check for table content
    query = new QSqlQuery();
    query->exec( "CREATE TABLE IF NOT EXISTS `posts` ( "
                 " `id` INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, `time` CHAR,"
                 " `date` CHAR, `post` TEXT)");
}

void dbworker::addPost(QString date,QString time,QString postText)
{
    QString execString;
    execString = "INSERT INTO posts (time,date,post) VALUES('"+time+"','"+date+"','"+postText+"')";
    query->exec(execString);
    if(query->lastError().text()!=" ")
        qDebug()<<query->lastError().text();
}

QStringList dbworker::getDateList()
{
    //qDebug()<<query->exec("SELECT * FROM posts");
    qDebug()<<query->exec("select date, count(*) from posts group by date having count(*) > 0");
    qDebug()<<query->lastError().text();
    QStringList dateList;
    while (query->next())
    {
        dateList<<query->value(0).toString();
    }
    qDebug()<<dateList;
    return dateList;
}

QString dbworker::getPostsByDate(QString date)
{
    qDebug()<<query->exec("SELECT * FROM posts where date = '"+date+"'");
    qDebug()<<query->lastError().text();
    QString textToDate;
    textToDate = "";
    while (query->next())
    {
        //qDebug()<<query->value(0).toString()<<query->value(1).toString()<<query->value(2).toString()<<query->value(3).toString();
        textToDate+="<h1>"+query->value(1).toString()+"</h1><br><br>"+query->value(3).toString()+"<br><hr>";
    }
    qDebug()<<textToDate;
    return textToDate;
}
