#ifndef MSGSELESAI_H
#define MSGSELESAI_H

#include <QMainWindow>
#include <qdebug.h>
#include <QDebug>
#include <QtDebug>

namespace Ui {
class msgselesai;
}

class msgselesai : public QMainWindow
{
    Q_OBJECT

public:
    explicit msgselesai(QWidget *parent = nullptr);
    ~msgselesai();

signals:
    void btnYesClicked();
    void btnNoClicked();

private slots:
    void on_btnYes_clicked();
    void on_btnNo_clicked();

private:
    Ui::msgselesai *ui;
};

#endif // msgselesai
