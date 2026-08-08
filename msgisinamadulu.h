#ifndef MSGISINAMADULU_H
#define MSGISINAMADULU_H

#include <QMainWindow>
#include <qdebug.h>
#include <QDebug>
#include <QtDebug>

namespace Ui {
class msgisinamadulu;
}

class msgisinamadulu : public QMainWindow
{
    Q_OBJECT

public:
    explicit msgisinamadulu(QWidget *parent = nullptr);
    ~msgisinamadulu();

signals:
    void btnYesClicked();

private slots:
    void on_btnYes_clicked();

private:
    Ui::msgisinamadulu *ui;
};

#endif // msgselesai
