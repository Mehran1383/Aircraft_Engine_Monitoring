#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_settings(new SettingsDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Flight Control"));

    // Create Gauge Widgets
    m_OilPressureGauge = new QcGaugeWidget;
    m_OilPressureNeedle = new QcNeedleItem;

    m_OilTemperatureGauge = new QcGaugeWidget;
    m_OilTemperatureNeedle = new QcNeedleItem;

    m_FuelGauge = new QcGaugeWidget;
    m_FuelNeedle = new QcNeedleItem;

    m_TorqueGauge = new QcGaugeWidget;
    m_TorqueNeedle = new QcNeedleItem;

    m_MotorSpeedGauge = new QcGaugeWidget;
    m_MotorSpeedNeedle = new QcNeedleItem;

    // Color settings
    QList<QPair<QColor,float>> OilPressure_color, OilTemperature_color, Fuel_color, Torque_color, MotorSpeed_color;
    OilPressure_color.append({Qt::darkGreen,30});
    OilPressure_color.append({Qt::yellow,70});
    OilPressure_color.append({Qt::red,100});

    OilTemperature_color.append({Qt::darkGreen,30});
    OilTemperature_color.append({Qt::yellow,70});
    OilTemperature_color.append({Qt::red,100});

    Fuel_color.append({Qt::red,30});
    Fuel_color.append({Qt::yellow,70});
    Fuel_color.append({Qt::darkGreen,100});

    Torque_color.append({Qt::darkGreen,30});
    Torque_color.append({Qt::yellow,70});
    Torque_color.append({Qt::red,100});

    MotorSpeed_color.append({Qt::darkGreen,50});
    MotorSpeed_color.append({Qt::yellow,80});
    MotorSpeed_color.append({Qt::red,100});

    // Create Gauges
    createGauge(m_OilPressureGauge, m_OilPressureNeedle, "PSI", 100, OilPressure_color);
    createGauge(m_OilTemperatureGauge, m_OilTemperatureNeedle, " C°", 40, OilTemperature_color);
    createGauge(m_FuelGauge, m_FuelNeedle, "Liter", 80, Fuel_color);
    createGauge(m_TorqueGauge, m_TorqueNeedle, "N.m", 40, Torque_color);
    createGauge(m_MotorSpeedGauge, m_MotorSpeedNeedle, "Km/h", 100, MotorSpeed_color);

    // Create GroupBoxes and set titles
    OIL_PRESSURE_box.setTitle("OIL PRESSURE");
    OIL_TEMPERATURE_box.setTitle("OIL TEMPERATURE");
    FUEL_box.setTitle("FUEL");
    TORQUE_box.setTitle("TORQUE");
    MOTOR_SPEED_box.setTitle("MOTOR SPEED");

    // Create Layouts and add widgets
    OIL_PRESSURE_layout.addWidget(m_OilPressureGauge);
    OIL_TEMPERATURE_layout.addWidget(m_OilTemperatureGauge);
    FUEL_layout.addWidget(m_FuelGauge);
    TORQUE_layout.addWidget(m_TorqueGauge);
    MOTOR_SPEED_layout.addWidget(m_MotorSpeedGauge);

    OIL_PRESSURE_box.setLayout(&OIL_PRESSURE_layout);
    OIL_TEMPERATURE_box.setLayout(&OIL_TEMPERATURE_layout);
    FUEL_box.setLayout(&FUEL_layout);
    TORQUE_box.setLayout(&TORQUE_layout);
    MOTOR_SPEED_box.setLayout(&MOTOR_SPEED_layout);

    // Main Layout
    main_layout.addWidget(&OIL_PRESSURE_box);
    main_layout.addWidget(&OIL_TEMPERATURE_box);
    main_layout.addWidget(&FUEL_box);
    main_layout.addWidget(&TORQUE_box);
    main_layout.addWidget(&MOTOR_SPEED_box);

    main_widget.setLayout(&main_layout);


    ui->widget->addPage("Sensor Error",&sensor_error);

    // Add main widget to widget container
    ui->widget->addPage("Gauge Panel", &main_widget);

    // Plot setup
    createPlot(&plot);
    plot_layout.addWidget(&plot);
    plot_widget.setLayout(&plot_layout);
    ui->widget->addPage("Plot Panel", &plot_widget);

    // Tray Icon Setup
    createActions();
    createTrayIcon();
    m_trayIcon->show();
    m_trayIcon->setIcon(QIcon(":/img/img/flight-icon.jfif"));
    setWindowIcon(QIcon(":/img/img/flight-icon.jfif"));

    // Initialize connection status and message handler
    connection_status = 0;
    messageHandler = new Process_message;
    messageHandler->setSpeedNeedle(this->m_OilPressureNeedle);

    // Create thread for message handler
    thread = new QThread;
    messageHandler->moveToThread(thread);
    thread->start();

    // Serial port and timer setup
    m_port = new QSerialPort(this);
    m_ScanTimer = new QTimer(this);
    m_ScanTimer->setInterval(20);
    connect(m_ScanTimer, &QTimer::timeout, this, &MainWindow::wait_for_data);
    connect(m_port, &QSerialPort::readyRead, this, &MainWindow::read_data);
    connect(this, &MainWindow::startProcess, messageHandler, &Process_message::processData);
}


MainWindow::~MainWindow()
{
    disconnect(m_ScanTimer, &QTimer::timeout, this, &MainWindow::wait_for_data);
    disconnect(m_port, &QSerialPort::readyRead, this, &MainWindow::read_data);
    disconnect(this, &MainWindow::startProcess, messageHandler, &Process_message::processData);

    thread->quit();
    thread->wait();

    delete messageHandler;
    delete m_port;
    delete m_ScanTimer;
    delete m_trayIcon;
    delete m_trayIconMenu;

    delete ui;
    delete m_settings;
}


void MainWindow::read_data()
{
    qDebug() << "data received";
    QByteArray data = m_port->readAll();
    messageHandler->setRawData(data);
    emit startProcess();

}

void MainWindow::on_connectButton_clicked()
{
    if (connection_status) {
        qDebug() << "disconnecting!";
        m_port->close();
        connection_status = 0;
        m_ScanTimer->stop();
        return;
    }

    const SettingsDialog::Settings setting = m_settings->settings();
    m_port->setPortName(setting.name);
    m_port->setBaudRate(setting.baudRate);
    m_port->setDataBits(setting.dataBits);
    m_port->setParity(setting.parity);
    m_port->setStopBits(setting.stopBits);
    m_port->setFlowControl(setting.flowControl);

    if(m_port->open(QIODevice::ReadOnly)) {
        qDebug() << "SERIAL: OK!";
        connection_status = 1;
        m_ScanTimer->start();
        if(setting.notification){
            showMessage("Connected Successfully", setting.name);
        }
    } else {
        qDebug() << "SERIAL: ERROR!";
    }

}


void MainWindow::wait_for_data()
{
    if(m_port->isOpen()){
        m_port->waitForReadyRead(1);
    }
}

void MainWindow::createGauge(QcGaugeWidget* m_gauge, QcNeedleItem* m_needle, QString title, int range, QList<QPair<QColor,float>> colorList)
{
    m_gauge->addBackground(99);
    QcBackgroundItem *bkg1 = m_gauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1f,Qt::black);
    bkg1->addColor(1.0f,Qt::white);

    QcBackgroundItem *bkg2 = m_gauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1f,Qt::gray);
    bkg2->addColor(1.0f,Qt::darkGray);

    m_gauge->addArc(55);
    m_gauge->addDegrees(65)->setValueRange(0,range);
    m_gauge->addColorBand(50, colorList);

    m_gauge->addValues(80)->setValueRange(0,range);

    m_gauge->addLabel(55)->setText("× 10");
    m_gauge->addLabel(70)->setText(title);
    QcLabelItem *lab = m_gauge->addLabel(35);
    lab->setText("0");
    m_needle = m_gauge->addNeedle(60);
    m_needle->setLabel(lab);
    m_needle->setColor(Qt::white);
    m_needle->setValueRange(0,range);
    m_gauge->addBackground(7);
    m_gauge->addGlass(88);

}

void MainWindow::createPlot(QCustomPlot* plot)
{
    plot->addGraph();
    plot->graph()->setPen(QPen(Qt::blue));
    plot->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
    plot->addGraph();
    plot->graph()->setPen(QPen(Qt::red));
    plot->axisRect()->setupFullAxesBox(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_setting_clicked()
{
    m_settings->show();
}

void MainWindow::showMessage(QString title, QString body)
{
    m_trayIcon->showMessage(title, body, QIcon(":/img/img/flight-icon.jfif"), 5000);
}

void MainWindow::createActions()
{
    m_minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(m_minimizeAction, &QAction::triggered, this, &QWidget::hide);

    m_maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(m_maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    m_restoreAction = new QAction(tr("&Restore"), this);
    connect(m_restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    m_quitAction = new QAction(tr("&Quit"), this);
    connect(m_quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainWindow::createTrayIcon()
{
    // Create the context menu
    m_trayIconMenu = new QMenu(this);
    m_trayIconMenu->addAction(m_minimizeAction);
    m_trayIconMenu->addAction(m_maximizeAction);
    m_trayIconMenu->addAction(m_restoreAction);
    m_trayIconMenu->addSeparator();
    m_trayIconMenu->addAction(m_quitAction);

    // Create the tray icon
    m_trayIcon = new QSystemTrayIcon(this);

    // Set the icon for the tray
    m_trayIcon->setIcon(QIcon(":/img/img/flight-icon.jfif"));

    // Set the context menu for the tray icon
    m_trayIcon->setContextMenu(m_trayIconMenu);

    // Make the tray icon visible
    m_trayIcon->setVisible(true);
}

