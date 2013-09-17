#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	curent = new QDateTime();
	qDebug()<< "\n\n\n=============================APP STARTED=========================";
	qDebug()<<curent->currentDateTime().toString(Qt::ISODate);
    core = new dbworker("mydb.sqlite");
    postAdd = new postWindow();
	this->setWindowTitle("QDiary-"+curent->currentDateTime().date().currentDate().toString(Qt::ISODate));
	generalSetting = new QSettings("Settings",QSettings::IniFormat,this);
	ui->setupUi(this);
	connect(ui->prefButton,SIGNAL(clicked()),this,SLOT(showPref()));
    connect(ui->newPostButton,SIGNAL(clicked()),this,SLOT(showPostWindow()));
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
	///connect area
	connect(ui->tableView,SIGNAL(cellClicked(int,int)),this,SLOT(showTextByDate(int,int)));
    connect(postAdd,SIGNAL(addPostToDb(QString)),this,SLOT(appendPostToDb(QString)));
    connect(postAdd,SIGNAL(postAdded()),this,SLOT(loadDiary()));
	///connect area

	//load diary data
	loadDiary();

}

void MainWindow::setTable(QStringList date)
{
    ui->tableView->clear();
    ui->tableView->setRowCount(0);
	for(int i=0;i<=date.count()-1;i++)
	{
		int lastRow = ui->tableView->rowCount();
		ui->tableView->insertRow(lastRow);
		QTableWidgetItem *item=new QTableWidgetItem (date[i]);
		ui->tableView->setItem(lastRow,0,item);
	}
}

void MainWindow::postData()
{

}

void MainWindow::showTextByDate(int row, int /*collumn*/)
{
    ui->webView->setHtml(core->getPostsByDate(ui->tableView->item(row,0)->text()));
}

void MainWindow::showPostWindow()    //show an new post window
{
    postAdd->show();    //postAdd is a class of new post window
}

void MainWindow::appendPostToDb(QString post)
{
    post.replace("\n","<br>");
    core->addPost(curent->date().currentDate().toString(Qt::ISODate),curent->time().currentTime().toString(Qt::ISODate),post);
}

void MainWindow::loadDiary()
{
    setTable(core->getDateList());
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
