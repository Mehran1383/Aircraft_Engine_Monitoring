#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->connectButton->setDisabled(1);

    connection_status = 0;

    m_Serial = new QSerialPort(this);
    updateSerialPorts();

    m_ScanTimer = new QTimer(this);
    m_ScanTimer->setInterval(5000);
    m_ScanTimer->start();

    connect(m_ScanTimer, &QTimer::timeout,
            this, &MainWindow::updateSerialPorts);

    connect(m_Serial, &QSerialPort::readyRead,
            this, &MainWindow::serialReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateSerialPorts()
{
    m_SerialPorts = QSerialPortInfo::availablePorts();

    ui->Port_comboBox->clear();
    for (QSerialPortInfo port : m_SerialPorts) {
        ui->Port_comboBox->addItem(port.portName());
    }
}

void MainWindow::serialReadyRead()
{
    QByteArray data = m_Serial->readAll();
    QString str = QString(data);
    ui->textBrowser->insertPlainText(str);
    QScrollBar* m_Scroll = ui->textBrowser->verticalScrollBar();
    m_Scroll->setValue(m_Scroll->maximum());
}

void MainWindow::on_connectButton_clicked()
{
    ui->connectButton->setDisabled(1);
    ui->Port_comboBox->setDisabled(1);

    QString serialLoc  =  ui->Port_comboBox->currentData().toString();

    if (connection_status) {
        qDebug() << "disconnecting!";
        m_Serial->close();
        connection_status = 0;
        ui->connectButton->setText("Connect");
        ui->connectButton->setDisabled(0);
        ui->Port_comboBox->setDisabled(0);
        return;
    }

    m_Serial->setPortName(serialLoc);
    m_Serial->setBaudRate(QSerialPort::Baud115200);
    m_Serial->setDataBits(QSerialPort::Data8);
    m_Serial->setParity(QSerialPort::NoParity);
    m_Serial->setStopBits(QSerialPort::OneStop);
    m_Serial->setFlowControl(QSerialPort::NoFlowControl);

    if(m_Serial->open(QIODevice::ReadOnly)) {
        qDebug() << "SERIAL: OK!";
        connection_status = 1;
        ui->connectButton->setText("Disconnect");
    } else {
        qDebug() << "SERIAL: ERROR!";
        ui->Port_comboBox->setDisabled(0);
    }
    ui->connectButton->setDisabled(0);
}

void MainWindow::on_Port_comboBox_currentIndexChanged(int index)
{
    if(index != -1){
        ui->connectButton->setDisabled(0);
    }
}
