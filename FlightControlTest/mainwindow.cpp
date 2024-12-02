#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    msg_counter = 0;

    m_ScanTimer = new QTimer();
    m_port = new QSerialPort();

    m_ScanTimer->setInterval(20);

    m_port->setPortName("COM1");
    m_port->setBaudRate(QSerialPort::Baud115200);
    m_port->setDataBits(QSerialPort::Data8);
    m_port->setParity(QSerialPort::NoParity);
    m_port->setStopBits(QSerialPort::OneStop);
    m_port->setFlowControl(QSerialPort::NoFlowControl);

    if(m_port->open(QIODevice::WriteOnly)) {
        qDebug() << "SERIAL: OK!";
        m_ScanTimer->start();
    } else {
        qDebug() << "SERIAL: ERROR!";
    }

    connect(m_ScanTimer, &QTimer::timeout,
            this, &MainWindow::wait_for_data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendData()
{
    m_mtx.lock();
    QByteArray array;
    uint8_t ID_Number = 8;
    uint8_t id;
    uint16_t checksum = 0;
    char byte[4];
    checksum = msg_counter + ID_Number;
    array.append(char(HEADER_VALUE));
    array.append(char(HEADER_VALUE));
    array.append(char(HEADER_VALUE));
    array.append(char(HEADER_VALUE));
    array.append(char(msg_counter));
    array.append(char(ID_Number));
    id = char(OIL_PRESSURE);
    int oilPressureData = QRandomGenerator::global()->bounded(0, 1000);
    int oilPressureFactor = QRandomGenerator::global()->bounded(1, 3);
    checksum += uint8_t(OIL_PRESSURE);
    array.append(char(id));
    array.append(char(0));
    packData(oilPressureData, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    packData(oilPressureFactor, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    id = char(OIL_TEMPERATURE);
    int oilTemperatureData = QRandomGenerator::global()->bounded(0, 400);
    int oilTemperatureFactor = QRandomGenerator::global()->bounded(1, 3);
    checksum += uint8_t(OIL_TEMPERATURE);
    array.append(char(id));
    array.append(char(0));
    packData(oilTemperatureData, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    packData(oilTemperatureFactor, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    id = char(FUEL_FLOW);
    int FuelFlowData = QRandomGenerator::global()->bounded(0, 800);
    int FuelFlowFactor = QRandomGenerator::global()->bounded(1, 3);
    checksum += uint8_t(FUEL_FLOW);
    array.append(char(id));
    array.append(char(0));
    packData(FuelFlowData, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    packData(FuelFlowFactor, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    id = char(FUEL);
    int FuelData = QRandomGenerator::global()->bounded(0, 800);
    int FuelFactor = QRandomGenerator::global()->bounded(1, 3);
    checksum += uint8_t(FUEL);
    array.append(char(id));
    array.append(char(0));
    packData(FuelData, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    packData(FuelFactor, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    id = char(EGT);
    int EgtData = QRandomGenerator::global()->bounded(0, 400);
    int EgtFactor = QRandomGenerator::global()->bounded(1, 3);
    checksum += uint8_t(EGT);
    array.append(char(id));
    array.append(char(0));
    packData(EgtData, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    packData(EgtFactor, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    id = char(TORQUE);
    int TorqueData = QRandomGenerator::global()->bounded(0, 400);
    int TorqueFactor = QRandomGenerator::global()->bounded(1, 3);
    checksum += uint8_t(TORQUE);
    array.append(char(id));
    array.append(char(0));
    packData(TorqueData, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    packData(TorqueFactor, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    id = char(MOTOR_SPEED);
    int MotorSpeedData = QRandomGenerator::global()->bounded(0, 1000);
    int MotorSpeedFactor = QRandomGenerator::global()->bounded(1, 3);
    checksum += uint8_t(MOTOR_SPEED);
    array.append(char(id));
    array.append(char(0));
    packData(MotorSpeedData, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    packData(MotorSpeedFactor, byte);
    array.append(byte[0]);
    array.append(byte[1]);
    array.append(byte[2]);
    array.append(byte[3]);
    checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));

    if(msg_counter % 2 == 0){

        id = char(EGT_SENSOR_ERROR);
        checksum += uint8_t(EGT_SENSOR_ERROR);
        array.append(char(id));
        array.append(char(0));
        packData(0, byte);
        array.append(byte[0]);
        array.append(byte[1]);
        array.append(byte[2]);
        array.append(byte[3]);
        checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
        packData(1, byte);
        array.append(byte[0]);
        array.append(byte[1]);
        array.append(byte[2]);
        array.append(byte[3]);
        checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    }

    else {
        id = char(EGT_SENSOR_ERROR);
        checksum += uint8_t(EGT_SENSOR_ERROR);
        array.append(char(id));
        array.append(char(0));
        packData(1, byte);
        array.append(byte[0]);
        array.append(byte[1]);
        array.append(byte[2]);
        array.append(byte[3]);
        checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
        packData(1, byte);
        array.append(byte[0]);
        array.append(byte[1]);
        array.append(byte[2]);
        array.append(byte[3]);
        checksum += (uint8_t(byte[0])) + (uint8_t(byte[1])) + (uint8_t(byte[2])) + (uint8_t(byte[3]));
    }
    char Byte[2];
    packData2(checksum, Byte);
    array.append(Byte[0]);
    array.append(Byte[1]);
    array.append(char(FOOTER_VALUE));

    m_port->write(array);

    if(msg_counter == 255) msg_counter = 0;
    else msg_counter++;
    qDebug() << "send successfully";
    m_mtx.unlock();

}

void MainWindow::packData(int data, char* byte)
{
    byte[0] = char( data & 0x000000FF);
    byte[1] = char((data & 0x0000FF00) >> 8) ;
    byte[2] = char((data & 0x00FF0000) >> 16);
    byte[3] = char(((uint32_t(data)) & 0xFF000000) >> 24);
}

void MainWindow::packData2(int data, char* byte)
{
    byte[0] = char( data & 0x00FF);
    byte[1] = char((data & 0xFF00) >> 8) ;

}

void MainWindow::wait_for_data()
{
    if(m_port->isOpen()){
        sendData();
        m_port->waitForBytesWritten(20);
    }
}
