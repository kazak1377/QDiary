#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    curent = new QDateTime();
    qDebug()<<"\n\n\n=============================APP STARTED=========================";
    qDebug()<<curent->currentDateTime().toString(Qt::ISODate);
    core = new dbworker("mydb.sqlite");
    settingsWindow = new prefWindow();
    postAdd = new postWindow();
    isProtected = true;
    this->setWindowTitle("QDiary-"+curent->currentDateTime().date().currentDate().toString(Qt::ISODate));
    generalSetting = new QSettings("Settings",QSettings::IniFormat,this);
    ui->setupUi(this);
    path = new QUrl("diary.xml");


    ///table setting
    ///set table header
    QStringList header;
    ui->tableView->setColumnCount(1);
    header <<tr("Date");
    ui->tableView->setHorizontalHeaderLabels(header); 	//set table header
    ui->tableView->setShowGrid(false);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->verticalHeader()->setVisible(false);

    //load our program settings
    connect(this,SIGNAL(settingsLoaded(bool)),settingsWindow,SLOT(loadSetting(bool)));
    loadSettings();
    //encrypedPassword = encryptPass("max1355");
    if(isProtected)
    {
        bool bOk;
        QString str = QInputDialog::getText( 0,"PROTECTED","Enter password:",QLineEdit::Password,"",&bOk);
        //hasher.addData();
        if (!bOk ||  !comparePass(str,encrypedPassword))
        {
            //Cencel was pressed
            qDebug()<<"opening cenceled.... Now program will be closed. Any other debug info is a trash";
            QTimer::singleShot(0, this, SLOT(close()));//close window on cencel
        }
    }
    ///connect area
    connect(ui->prefButton,SIGNAL(clicked()),this,SLOT(showPref()));
    connect(ui->newPostButton,SIGNAL(clicked()),this,SLOT(showPostWindow()));
    connect(ui->tableView,SIGNAL(cellClicked(int,int)),this,SLOT(showTextByDate(int,int)));
    connect(postAdd,SIGNAL(addPostToDb(QString)),this,SLOT(appendPostToDb(QString)));
    connect(postAdd,SIGNAL(postAdded()),this,SLOT(loadDiary()));
    connect(settingsWindow,SIGNAL(protectionChanged(bool)),this,SLOT(changeSettings(bool)));
    connect(settingsWindow,SIGNAL(passChenged(QString)),this,SLOT(changePass(QString)));
    ///connect area
    ui->webView->setHtml("<h1>Click the date to see your posts</h1>");
    //load diary data
    loadDiary();

}

void MainWindow::setTable(QStringList date)
{
    ui->tableView->clear();
    ui->tableView->setRowCount(0);
    QStringList header;
    ui->tableView->setColumnCount(1);
    header <<tr("Date");
    ui->tableView->setHorizontalHeaderLabels(header); 	//set table header
    for(int i=0;i<=date.count()-1;i++)
    {
        int lastRow = ui->tableView->rowCount();
        ui->tableView->insertRow(lastRow);
        QTableWidgetItem *item=new QTableWidgetItem (date[i]);
        ui->tableView->setItem(lastRow,0,item);
    }
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

void MainWindow::changeSettings(bool is)
{
    if(encrypedPassword != "")
        isProtected = is;
    else
    {
        int r = QMessageBox::warning(settingsWindow, tr("Warning"),
                        tr("There is no password. Set the password first!"),
                        QMessageBox::Ok);
        isProtected = false;
        emit settingsLoaded(isProtected);
    }
}

void MainWindow::changePass(QString newPass)
{
    qDebug()<<"pass changed: "<<newPass;
    encrypedPassword = encryptPass(newPass);
}

void MainWindow::saveSettings()
{
    qDebug()<<"saving settings";
    generalSetting->setValue("path",this->path->toString());
    generalSetting->setValue("geometry",saveGeometry());
    generalSetting->setValue("listWidth",ui->splitter->saveState());
    generalSetting->setValue("password",encrypedPassword);
    qDebug()<<"saved pass hash: "+encrypedPassword;
    generalSetting->setValue("isProtected",isProtected);
    qDebug()<<"isProtected: "<<isProtected;
    qDebug()<<"saving settings done";
}

void MainWindow::loadSettings()
{
    qDebug()<<"loading settings";
    ui->splitter->restoreState(generalSetting->value("listWidth",ui->splitter->saveState()).toByteArray());
    restoreGeometry(generalSetting->value("geometry",saveGeometry()).toByteArray());
    *path = generalSetting->value("path","diary.xml").toUrl();
    encrypedPassword = generalSetting->value("password","").toByteArray();
    qDebug()<<"Loaded pass hash: "+encrypedPassword;
    isProtected = generalSetting->value("isProtected",false).toBool();
    qDebug()<<"isProtected: "<<isProtected;
    emit settingsLoaded(isProtected);
    qDebug()<<"loading settings done";
}

void MainWindow::showPref()
{
    settingsWindow->show();
}

bool MainWindow::comparePass(QString entered,QByteArray saved)
{
    QCryptographicHash hasher(QCryptographicHash::Sha1);
    QByteArray sr="";
    sr.append(entered);
    hasher.addData(sr);
    QByteArray string2=hasher.result();
    qDebug()<<"Entered pass hash"<<string2;
    qDebug()<<"Correct pass hash"<<saved;
    if(string2==saved)
        return true;
    else
        return false;
}

QByteArray MainWindow::encryptPass(QString pass)
{
    qDebug()<<pass;
    QCryptographicHash hasher(QCryptographicHash::Sha1);
    QByteArray sr="";
    sr.append(pass);
    hasher.addData(sr);
    QByteArray string1=hasher.result();
    qDebug()<<string1;             //encrypted pass
    return string1;
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
    qDebug()<<"=============================APP CLOSED========================= ";
}
