#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QRandomGenerator>
#include <QMutex>

#define HEADER_VALUE 0xa5
#define FOOTER_VALUE 0x55

#define OIL_PRESSURE       0x01
#define OIL_TEMPERATURE    0x02
#define FUEL_FLOW          0x03
#define FUEL               0x04
#define EGT                0x05
#define TORQUE             0x06
#define INDICATED_POWER    0x07
#define FRICTIONAL_POWER   0x08
#define THERMAL_EFFICIENCY 0x09
#define AIR_FUEL_RATIO     0x0a
#define MOTOR_SPEED        0x0b
#define OUTPUT_AIR_SPEED   0x0c
#define VIBRATION          0x0d
#define BODY_TEMP          0x0e
#define AIR_TEMP           0x0f

#define OIL_PRESSURE_SENSOR_ERROR       0x11
#define OIL_TEMPERATURE_SENSOR_ERROR    0x12
#define FUEL_FLOW_SENSOR_ERROR          0x13
#define FUEL_SENSOR_ERROR               0x14
#define EGT_SENSOR_ERROR                0x15
#define TORQUE_SENSOR_ERROR             0x16
#define INDICATED_POWER_SENSOR_ERROR    0x17
#define FRICTIONAL_POWER_SENSOR_ERROR   0x18
#define THERMAL_EFFICIENCY_SENSOR_ERROR 0x19
#define AIR_FUEL_RATIO_SENSOR_ERROR     0x1a
#define MOTOR_SPEED_SENSOR_ERROR        0x1b
#define OUTPUT_AIR_SPEED_SENSOR_ERROR   0x1c
#define VIBRATION_SENSOR_ERROR          0x1d
#define BODY_TEMP_SENSOR_ERROR          0x1e
#define AIR_TEMP_SENSOR_ERROR           0x1f

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void sendData();
    void packData(int, char*);
    void packData2(int, char*);

    QMutex m_mtx;

public slots:
    void wait_for_data();

private:
    Ui::MainWindow *ui;

    QTimer* m_ScanTimer;
    QSerialPort* m_port;
    uint8_t msg_counter;

};
#endif // MAINWINDOW_H
