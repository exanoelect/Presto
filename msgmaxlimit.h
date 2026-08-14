#ifndef MSGMAXLIMIT_H
#define MSGMAXLIMIT_H

#include <QMainWindow>
#include <qdebug.h>
#include <QDebug>
#include <QtDebug>

namespace Ui {
class msgmaxlimit;
}

class msgmaxlimit : public QMainWindow
{
    Q_OBJECT

public:
    explicit msgmaxlimit(QWidget *parent = nullptr);
    ~msgmaxlimit();

signals:
    void btnYesClicked();

private slots:
    void on_btnYes_clicked();

private:
    Ui::msgmaxlimit *ui;
};

#endif // msgendukur_H
