#include "prefwindow.h"
#include "ui_prefwindow.h"
#include "QDebug"

prefWindow::prefWindow(QWidget *parent) : QWidget(parent), ui(new Ui::prefWindow)
{
    ui->setupUi(this);
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SIGNAL(protectionChanged(bool)));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(changePass()));
}

prefWindow::~prefWindow()
{
    delete ui;
}

void prefWindow::loadSetting(bool protection)
{
    qDebug()<<"checkBox: "<<protection;
    ui->checkBox->setChecked(protection);
}

void prefWindow::changePass()
{
    QString pass;
    pass = ui->lineEdit->text();
    emit passChenged(pass);
}
