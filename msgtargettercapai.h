#ifndef MSGTARGETERCAPAI_H
#define MSGTARGETERCAPAI_H

#include <QMainWindow>
#include <qdebug.h>
#include <QDebug>
#include <QtDebug>

namespace Ui {
class msgtargetercapai;
}

class msgtargetercapai : public QMainWindow
{
    Q_OBJECT

public:
    explicit msgtargetercapai(QWidget *parent = nullptr);
    ~msgtargetercapai();

signals:
    void btnYesClicked();

private slots:
    void on_btnYes_clicked();

private:
    Ui::msgtargetercapai *ui;
};

#endif // msgselesai
