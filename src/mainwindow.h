#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_connectButton_clicked();
    void serialReadyRead();

    void on_Port_comboBox_currentIndexChanged(int index);

private:
    void updateSerialPorts();

private:
    Ui::MainWindow *ui;
    QSerialPort *m_Serial;
    QList<QSerialPortInfo> m_SerialPorts;
    QTimer *m_ScanTimer;
    bool connection_status;
};
#endif // MAINWINDOW_H
