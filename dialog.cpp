#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::recieveInfo(Dialog::st temp)
{
    ui->lokkod->setText(temp.lokKod);
    ui->name->setText(temp.name);
    ui->GCX->setText(QString::number(temp.GCX));
    ui->HCX->setText(QString::number(temp.HCX));
    ui->index->setText(temp.index);
    ui->aurum->setText(QString::number(temp.aurum));
    ui->argentum->setText(QString::number(temp.argentum));
    ui->platina->setText(QString::number(temp.platina));
    ui->platinaGroup->setText(QString::number(temp.platinaGroup));
    ui->edIzmer->setText(temp.edIzmer);
}
