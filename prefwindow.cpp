#include "prefwindow.h"
#include "ui_prefwindow.h"
#include "QDebug"
#include <QMessageBox>

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
    if(pass == "")
    {
        int r = QMessageBox::question(this, tr("Are you sure?"),
                        tr("Do you really want to use empty password?"),
                        QMessageBox::Ok|QMessageBox::Cancel);
        if(r == QMessageBox::Ok)
            emit passChenged(pass);
    }
    {
        /*int r = */QMessageBox::information(this, tr("Password changed"),
                        tr("Password was successfuly changed"),
                        QMessageBox::Ok);
        emit passChenged(pass);

    }
    ui->lineEdit->clear();
}
