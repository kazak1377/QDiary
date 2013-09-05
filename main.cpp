#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("kazak softworks");
    QCoreApplication::setOrganizationDomain("kazak1377.16mb.com");
    QCoreApplication::setApplicationName("QDiary");

    MainWindow w;
    w.show();
    
    return a.exec();
}
