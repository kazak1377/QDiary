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
#include "xmlworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QDateTime *curent;
    void loadDiary();
    QSettings *generalSetting;
    void saveSettings();
    void loadSettings();
	QUrl *path;
	QFile *xmlDiary;
    void setTable(QStringList date);
	QStringList line;
    QStringList postList;
    XmlWorker *core;
    void generatePostList(QString date);
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
};

#endif // MAINWINDOW_H
