#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QDateTime>

#include "process_message.h"
#include "gaugewidget.h"
#include "settingsdialog.h"
#include "qcustomplot.h"
#include "sensorerrortable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createGauge(QcGaugeWidget*, QcNeedleItem*, QString, int, QList<QPair<QColor,float>>);
    void showMessage(QString title, QString body);
    void createPlot(QCustomPlot*);
    void createTrayIcon();
    void createActions();

public slots:
    void on_connectButton_clicked();
    void on_setting_clicked();
    void read_data();
    void wait_for_data();
    void legendDoubleClick(QCPAbstractLegendItem* item);
    void contextMenuRequest(QPoint pos);
    void moveLegend();
    void updateGaugePanel();
    void updatePlotPanel();

signals:
    void startProcess();

private:
    Ui::MainWindow *ui;
    QSerialPort* m_port;
    QList<QSerialPortInfo> m_portList;
    QTimer* m_ScanTimer;
    Process_message* messageHandler;
    QThread* process_thread;
    QThread* serial_thread;
    QThread* timer_thread;
    QcGaugeWidget* m_OilPressureGauge;
    QcNeedleItem* m_OilPressureNeedle;
    QcGaugeWidget* m_OilTemperatureGauge;
    QcNeedleItem* m_OilTemperatureNeedle;
    QcGaugeWidget* m_FuelGauge;
    QcNeedleItem* m_FuelNeedle;
    QcNeedleItem* m_TorqueNeedle;
    QcGaugeWidget* m_TorqueGauge;
    QcNeedleItem* m_MotorSpeedNeedle;
    QcGaugeWidget* m_MotorSpeedGauge;
    SettingsDialog* m_settings;
    QSystemTrayIcon* m_trayIcon;
    QMenu* m_trayIconMenu;
    QAction* m_minimizeAction;
    QAction* m_maximizeAction;
    QAction* m_restoreAction;
    QAction* m_quitAction;
    QHBoxLayout main_layout;
    QHBoxLayout plot_layout;
    QVBoxLayout MOTOR_SPEED_layout;
    QGroupBox MOTOR_SPEED_box;
    QVBoxLayout TORQUE_layout;
    QGroupBox TORQUE_box;
    QVBoxLayout OIL_TEMPERATURE_layout;
    QGroupBox OIL_TEMPERATURE_box;
    QVBoxLayout FUEL_layout;
    QGroupBox FUEL_box;
    QVBoxLayout OIL_PRESSURE_layout;
    QGroupBox OIL_PRESSURE_box;
    QWidget main_widget;
    QWidget plot_widget;
    QCustomPlot plot;
    SensorErrorTable sensor_error;


    bool connection_status;
};
#endif // MAINWINDOW_H
