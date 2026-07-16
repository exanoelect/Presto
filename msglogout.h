#ifndef MSGLOGOUT_H
#define MSGLOGOUT_H

#include <QMainWindow>
#include <qdebug.h>
#include <QDebug>
#include <QtDebug>

namespace Ui {
class msglogout;
}

class msglogout : public QMainWindow
{
    Q_OBJECT

public:
    explicit msglogout(QWidget *parent = nullptr);
    ~msglogout();

signals:
    void btnYesClicked();
    void btnNoClicked();

private slots:
    void on_btnYes_clicked();
    void on_btnNo_clicked();

private:
    Ui::msglogout *ui;
};

#endif // MSGLOGOUT_H
