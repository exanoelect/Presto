#ifndef MSGENDUKUR_H
#define MSGENDUKUR_H

#include <QMainWindow>
#include <qdebug.h>
#include <QDebug>
#include <QtDebug>

namespace Ui {
class msgendukur;
}

class msgendukur : public QMainWindow
{
    Q_OBJECT

public:
    explicit msgendukur(QWidget *parent = nullptr);
    ~msgendukur();

signals:
    void btnYesClicked();
    void btnNoClicked();

private slots:
    void on_btnYes_clicked();
    void on_btnNo_clicked();

private:
    Ui::msgendukur *ui;
};

#endif // msgendukur_H
