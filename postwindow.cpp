#include "postwindow.h"
#include "ui_postwindow.h"
#include "QDebug"
#include <QMessageBox>

postWindow::postWindow(QWidget *parent) : QWidget(parent), ui(new Ui::postWindow)
{
    ui->setupUi(this);
    ui->styleBar->hide();
    connect(ui->postButton,SIGNAL(clicked()),this,SLOT(editingDone()));
    connect(ui->discardButton,SIGNAL(clicked()),this,SLOT(close()));
}

postWindow::~postWindow()
{
    delete ui;
}

void postWindow::editingDone()
{
    QString post = ui->textEdit->toPlainText();
    qDebug()<<post;
    emit addPostToDb(post);
    emit postAdded();
    this->deleteLater();
}
