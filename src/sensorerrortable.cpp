#include "sensorerrortable.h"
#include "ui_sensorerrortable.h"

SensorErrorTable::SensorErrorTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SensorErrorTable)
{
    ui->setupUi(this);
}

SensorErrorTable::~SensorErrorTable()
{
    delete ui;
}
