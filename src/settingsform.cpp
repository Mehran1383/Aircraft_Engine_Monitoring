#include "settingsform.h"
#include "ui_settingsform.h"
#include <QDebug>
#include <QScrollBar>

settingsForm::settingsForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::settingsForm)
{
    ui->setupUi(this);
    ui->connectButton->setDisabled(1);

    connection_status = 0;

    m_port = new QSerialPort(this);
    updateSerialPorts();

    m_ScanTimer = new QTimer(this);
    m_ScanTimer->setInterval(20);
    m_ScanTimer->start();

    connect(m_ScanTimer, &QTimer::timeout,
            this, &settingsForm::wait_for_data);

    connect(m_port, &QSerialPort::readyRead,
            this, &settingsForm::read_data);

}

void settingsForm::updateSerialPorts()
{
    m_portList = QSerialPortInfo::availablePorts();

    ui->Port_comboBox->clear();
    for (QSerialPortInfo port : m_portList) {
        //ui->Port_comboBox->addItem(port.portName());
        ui->Port_comboBox->addItem(port.portName(), port.systemLocation());
    }
}


void settingsForm::read_data()
{
    qDebug() << "data received";
    QByteArray data = m_port->readAll();
    //QString str = QString(data);
    const QString str = QString::fromUtf8(data);
    qDebug() << str;
    ui->textBrowser->insertPlainText(str);
    QScrollBar* m_Scroll = ui->textBrowser->verticalScrollBar();
    m_Scroll->setValue(m_Scroll->maximum());
}



void settingsForm::on_connectButton_clicked()
{
    ui->connectButton->setDisabled(1);
    ui->Port_comboBox->setDisabled(1);

    QString serialLoc  =  ui->Port_comboBox->currentText();
    //QString serialLoc  =  ui->Port_comboBox->currentData().toString();
    qDebug() << ui->Port_comboBox->currentText();
    qDebug() << ui->Port_comboBox->currentData().toString();

    if (connection_status) {
        qDebug() << "disconnecting!";
        m_port->close();
        connection_status = 0;
        ui->connectButton->setText("Connect");
        ui->connectButton->setDisabled(0);
        ui->Port_comboBox->setDisabled(0);
        return;
    }

    m_port->setPortName(serialLoc);
    m_port->setBaudRate(QSerialPort::Baud115200);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setFlowControl(QSerialPort::NoFlowControl);

    if(m_port->open(QIODevice::ReadOnly)) {
        qDebug() << "SERIAL: OK!";
        connection_status = 1;
        ui->connectButton->setText("Disconnect");
    } else {
        qDebug() << "SERIAL: ERROR!";
        ui->Port_comboBox->setDisabled(0);
    }
    ui->connectButton->setDisabled(0);

}


void settingsForm::on_Port_comboBox_currentIndexChanged(int index)
{
    if(index != -1){
        ui->connectButton->setDisabled(0);
    }
}

void settingsForm::wait_for_data(){
    if(m_port->isOpen()){
        m_port->waitForReadyRead(1);
    }
}



settingsForm::~settingsForm()
{
    delete ui;
}

void settingsForm::on_home_btn_clicked()
{
    emit HomeClicked();
}

