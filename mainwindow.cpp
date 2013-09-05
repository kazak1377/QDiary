#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	curent = new QDateTime();
	qDebug()<< "\n\n\n=============================APP STARTED=========================";
	qDebug()<<curent->currentDateTime().toString(Qt::ISODate);
	this->setWindowTitle("QDiary-"+curent->currentDateTime().date().currentDate().toString(Qt::ISODate));
	generalSetting = new QSettings("Settings",QSettings::IniFormat,this);
	ui->setupUi(this);
	connect(ui->prefButton,SIGNAL(clicked()),this,SLOT(showPref()));
	path = new QUrl("diary.xml");



	///table setting
	///set table header
	QStringList header;
	ui->tableView->setColumnCount(1);
	header <<tr("Date");
	//set table header
	ui->tableView->setHorizontalHeaderLabels(header);
	ui->tableView->setShowGrid(false);
	ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	//load our program settings
	loadSettings();
	xmlDiary = new QFile(path->toString());
	qDebug()<<xmlDiary->fileName();
	core = new XmlWorker(xmlDiary);
	///connect area
	connect(ui->tableView,SIGNAL(cellClicked(int,int)),this,SLOT(showTextByDate(int,int)));
	connect(core,SIGNAL(contentChanged(QString)),this,SLOT(saveDiary(QString)));
	///connect area

	//load diary data
	loadDiary();

}

void MainWindow::setTable(QStringList date)
{
	for(int i=0;i<=date.count()-1;i++)
	{
		int lastRow = ui->tableView->rowCount();
		ui->tableView->insertRow(lastRow);
		QTableWidgetItem *item=new QTableWidgetItem (date[i]);
		ui->tableView->setItem(lastRow,0,item);
	}
}

void MainWindow::generatePostList(QString date)
{
	postList = core->getElementsFromString(core->getElemetsWithArgs("date",date),"time");
}

void MainWindow::postData()
{

}

void MainWindow::showTextByDate(int row, int /*collumn*/)
{
	QStringList times;
	times = core->getValuesByTagNameFromString("time",core->getElemetsWithArgs("date",ui->tableView->item(row,0)->text())[0]);
	//postList.clear();
	generatePostList(ui->tableView->item(row,0)->text());
	QString postText = " ";
	for(int i=0;i<=postList.count()-1;i++)
	{
		postText+="<hr>";
		postText+="<h1>"+times[i]+"</h1>";
		postText+="</br><br>";
		postText+=postList[i];
	}
	ui->webView->setHtml(postText);
}

void MainWindow::loadDiary()
{
	setTable(core->getValuesByTagName("date"));
	//    postList = core->getElementsByTagName("posttext");
	qDebug()<<core->isBlockEmpty("date",curent->currentDateTime().date().currentDate().toString(Qt::ISODate));
	// if(!core->isBlockExist("date",curent->currentDateTime().date().currentDate().toString(Qt::ISODate)))
	// 	core->appendFirstLevelBlock("date",curent->currentDateTime().date().currentDate().toString(Qt::ISODate));
}

void MainWindow::saveSettings()
{
	generalSetting->setValue("path",this->path->toString());
	generalSetting->setValue("geometry",saveGeometry());
	generalSetting->setValue("listWidth",ui->splitter->saveState());
}

void MainWindow::loadSettings()
{
	ui->splitter->restoreState(generalSetting->value("listWidth",ui->splitter->saveState()).toByteArray());
	restoreGeometry(generalSetting->value("geometry",saveGeometry()).toByteArray());
	*path = generalSetting->value("path","diary.xml").toUrl();
}

void MainWindow::showPref()
{
	QQuickView *view = new QQuickView;
	view->setSource(QUrl::fromLocalFile("pref.qml"));
	view->setFlags(Qt::FramelessWindowHint);
	view->show();
}

void MainWindow::saveDiary(QString data)
{
	qDebug()<<"recived";
	xmlDiary->open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream toFile(xmlDiary);
	toFile << data;
	xmlDiary->close();
}

MainWindow::~MainWindow()
{
	//saveDiary();
	xmlDiary->close();
	saveSettings();
	delete ui;
}
