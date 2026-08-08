#include "msgisinamadulu.h"
#include "ui_msgisinamadulu.h"

msgisinamadulu::msgisinamadulu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::msgisinamadulu)
{
    ui->setupUi(this);
}

msgisinamadulu::~msgisinamadulu()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void msgisinamadulu::on_btnYes_clicked()
{
   emit btnYesClicked();
    this->deleteLater();
}


