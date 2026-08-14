#include "msgmaxlimit.h"
#include "ui_msgmaxlimit.h"

msgmaxlimit::msgmaxlimit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::msgmaxlimit)
{
    ui->setupUi(this);
}

msgmaxlimit::~msgmaxlimit()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void msgmaxlimit::on_btnYes_clicked()
{
   emit btnYesClicked();
    this->deleteLater();
}


