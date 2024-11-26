#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

namespace Ui {
class settingsForm;
}

class settingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit settingsForm(QWidget *parent = nullptr);
    ~settingsForm();


public slots:
    void on_connectButton_clicked();
    void on_Port_comboBox_currentIndexChanged(int index);
    void read_data();
    void wait_for_data();
    void on_home_btn_clicked();


private:
    void updateSerialPorts();


private:
    Ui::settingsForm *ui;
    QSerialPort* m_port;
    QList<QSerialPortInfo> m_portList;
    QTimer* m_ScanTimer;
    bool connection_status;


signals:
    void HomeClicked();

};

#endif // SETTINGSFORM_H
