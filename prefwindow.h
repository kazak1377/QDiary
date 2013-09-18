#ifndef PREFWINDOW_H
#define PREFWINDOW_H

#include <QWidget>

namespace Ui {
class prefWindow;
}

class prefWindow : public QWidget
{
    Q_OBJECT

public:
    explicit prefWindow(QWidget *parent = 0);
    ~prefWindow();

private:
    Ui::prefWindow *ui;
public slots:
    void loadSetting(bool);
    void changePass();
signals:
    void protectionChanged(bool);
    void passChenged(QString);
};

#endif // PREFWINDOW_H
