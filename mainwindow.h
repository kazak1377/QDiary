#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDateTime>
//#include <QtQuick/QtQuick>
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
#include "prefwindow.h"
#include <iostream>
#include <QInputDialog>
#include <QCryptographicHash>

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
    prefWindow *settingsWindow;
    QByteArray encrypedPassword;
    bool isProtected;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    bool comparePass(QString entered, QByteArray saved);
    QByteArray encryptPass(QString pass);
private slots:
    void showPref();
    void showTextByDate(int row, int);
    void showPostWindow();
    void appendPostToDb(QString post);
    void loadDiary();
public slots:
    void changeSettings(bool);
    void changePass(QString newPass);
signals:
    void settingsLoaded(bool);
};

#endif // MAINWINDOW_H
