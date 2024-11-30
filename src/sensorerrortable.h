#ifndef SENSORERRORTABLE_H
#define SENSORERRORTABLE_H

#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QTableWidgetItem>

#include "process_message.h"
#include "sensorerrordelegate.h"

namespace Ui {
class SensorErrorTable;
}

class SensorErrorTable : public QWidget
{
    Q_OBJECT

public:
    explicit SensorErrorTable(QWidget *parent = nullptr);
    ~SensorErrorTable();

    void setValue(QMap<char,float>);

private:
    QIcon iconSafe;
    QIcon iconDanger ;
    SensorErrorDelegate *delegate;
    QTableWidgetItem *oilPressureSensorItem;
    QTableWidgetItem *oilTemperatureSensorItem;
    QTableWidgetItem *fuelFlowSensorItem;
    QTableWidgetItem *fuelSensorItem;
    QTableWidgetItem *egtSensorItem;
    QTableWidgetItem *torqueSensorItem;
    QTableWidgetItem *indicatedPowerSensorItem;
    QTableWidgetItem *frictionalPowerSensorItem;
    QTableWidgetItem *thermalEfficiencySensorItem;
    QTableWidgetItem *airFuelRatioSensorItem;
    QTableWidgetItem *motorSpeedSensorItem;
    QTableWidgetItem *outputAirSpeedSensorItem;
    QTableWidgetItem *vibrationSensorItem;
    QTableWidgetItem *bodyTempSensorItem;
    QTableWidgetItem *airTempSensorItem;
    QTableWidgetItem *oilPressureItem;
    QTableWidgetItem *oilTemperatureItem;
    QTableWidgetItem *fuelFlowItem;
    QTableWidgetItem *fuelItem;
    QTableWidgetItem *egtItem;
    QTableWidgetItem *torqueItem;
    QTableWidgetItem *indicatedPowerItem;
    QTableWidgetItem *frictionalPowerItem;
    QTableWidgetItem *thermalEfficiencyItem;
    QTableWidgetItem *airFuelRatioItem;
    QTableWidgetItem *motorSpeedItem;
    QTableWidgetItem *outputAirSpeedItem;
    QTableWidgetItem *vibrationItem;
    QTableWidgetItem *bodyTempItem;
    QTableWidgetItem *airTempItem;
    Ui::SensorErrorTable *ui;
};

#endif // SENSORERRORTABLE_H
