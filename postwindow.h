#ifndef POSTWINDOW_H
#define POSTWINDOW_H

#include <QWidget>

namespace Ui {
class postWindow;
}

class postWindow : public QWidget
{
    Q_OBJECT

public:
    explicit postWindow(QWidget *parent = 0);
    ~postWindow();

private:
    Ui::postWindow *ui;

signals:
    void addPostToDb(QString post);
    void postAdded();
private slots:
    void editingDone();
};

#endif // POSTWINDOW_H
