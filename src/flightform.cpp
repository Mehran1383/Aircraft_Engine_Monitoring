#include "flightform.h"
#include "ui_flightform.h"

flightform::flightform(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::flightform)
{
    ui->setupUi(this);
}

flightform::~flightform()
{
    delete ui;
}

void flightform::on_home_btn_clicked()
{
    emit HomeClicked();
}

