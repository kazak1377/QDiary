#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDateTime>
#include <QtQuick/QtQuick>
#include <QDebug>
#include <QUrl>
#include <QMap>
#include <QFile>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QMapIterator>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDialog>
#include <QFileDialog>
#include <QtXml/QDomDocument>
#include <QDomDocument>
#include "dbworker.h"
#include "postwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QDateTime *curent;

    QSettings *generalSetting;
    void saveSettings();
    void loadSettings();
	QUrl *path;
	QFile *xmlDiary;
    void setTable(QStringList date);
	QStringList line;
    QStringList postList;
    void generatePostList(QString date);
    dbworker *core;
    postWindow *postAdd;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

private slots:
	void showPref();
	void postData();
    void saveDiary(QString data);
    void showTextByDate(int row, int);
    void showPostWindow();
    void appendPostToDb(QString post);
    void loadDiary();
};

#endif // MAINWINDOW_H
