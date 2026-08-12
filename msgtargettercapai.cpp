#include "msgtargettercapai.h"
#include "ui_msgtargetercapai.h"

msgtargetercapai::msgtargetercapai(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::msgtargetercapai)
{
    ui->setupUi(this);
}

msgtargetercapai::~msgtargetercapai()
{
    delete ui;
}

//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void msgtargetercapai::on_btnYes_clicked()
{
   emit btnYesClicked();
   this->deleteLater();
}


//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------
void msgtargetercapai::on_btnResume_clicked()
{
    emit btnResumeClicked();
    this->deleteLater();
}
