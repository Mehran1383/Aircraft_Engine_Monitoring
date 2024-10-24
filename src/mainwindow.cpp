#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Serial(new QSerialPort(this)),
    m_ScanTimer(new QTimer(this)),
    connection_status(false) 
{
    ui->setupUi(this);
    ui->connectButton->setDisabled(true); 

    updateSerialPorts(); 

    m_ScanTimer->setInterval(5000);
    connect(m_ScanTimer, &QTimer::timeout, this, &MainWindow::updateSerialPorts);
    m_ScanTimer->start();

    connect(m_Serial, &QSerialPort::readyRead, this, &MainWindow::serialReadyRead);
}

MainWindow::~MainWindow()
{
    delete ui; 
}

void MainWindow::updateSerialPorts()
{
    m_SerialPorts = QSerialPortInfo::availablePorts(); 

    ui->Port_comboBox->clear(); 
    for (const QSerialPortInfo &port : m_SerialPorts) {
        ui->Port_comboBox->addItem(port.portName());
    }

    if (m_SerialPorts.isEmpty()) {
        qDebug() << "No available serial ports found!";
    } else {
        for (const QSerialPortInfo &port : m_SerialPorts) {
            qDebug() << "Available port:" << port.portName();
        }
    }
}

void MainWindow::serialReadyRead()
{
    QByteArray data = m_Serial->readAll(); 
    QString str = QString::fromUtf8(data); 
    ui->textBrowser->insertPlainText(str); 

    QScrollBar *m_Scroll = ui->textBrowser->verticalScrollBar();
    m_Scroll->setValue(m_Scroll->maximum());
}

void MainWindow::on_connectButton_clicked()
{
    ui->connectButton->setDisabled(true); 
    ui->Port_comboBox->setDisabled(true); 

    QString serialLoc = ui->Port_comboBox->currentText(); 

    if (connection_status) { 
        qDebug() << "Disconnecting!";
        m_Serial->close();
        connection_status = false;
        ui->connectButton->setText("Connect");
    } else {
        m_Serial->setPortName(serialLoc);
        m_Serial->setBaudRate(QSerialPort::Baud115200);
        m_Serial->setDataBits(QSerialPort::Data8);
        m_Serial->setParity(QSerialPort::NoParity);
        m_Serial->setStopBits(QSerialPort::OneStop);
        m_Serial->setFlowControl(QSerialPort::NoFlowControl);

        if (m_Serial->open(QIODevice::ReadOnly)) {
            qDebug() << "SERIAL: Connection successful!";
            connection_status = true;
            ui->connectButton->setText("Disconnect");
        } else {
            qDebug() << "SERIAL: Connection failed with error:" << m_Serial->errorString();
            ui->Port_comboBox->setDisabled(false);
        }
    }

    ui->connectButton->setDisabled(false); 
}

void MainWindow::on_Port_comboBox_currentIndexChanged(int index)
{
    ui->connectButton->setDisabled(index == -1);
}
