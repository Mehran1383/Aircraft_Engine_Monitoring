#include "sensorerrortable.h"
#include "ui_sensorerrortable.h"


SensorErrorTable::SensorErrorTable(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SensorErrorTable)
{
    ui->setupUi(this);
    delegate = new SensorErrorDelegate(this);
    ui->sensorErrorTable->setItemDelegateForColumn(2, delegate);

    ui->sensorErrorTable->resizeColumnsToContents();
    ui->sensorErrorTable->resizeRowsToContents();
    ui->sensorOtherTable->resizeColumnsToContents();
    ui->sensorOtherTable->resizeRowsToContents();

    oilPressureSensorItem = new QTableWidgetItem();
    oilTemperatureSensorItem = new QTableWidgetItem();
    fuelFlowSensorItem = new QTableWidgetItem();
    fuelSensorItem = new QTableWidgetItem();
    egtSensorItem = new QTableWidgetItem();
    torqueSensorItem = new QTableWidgetItem();
    indicatedPowerSensorItem = new QTableWidgetItem();
    frictionalPowerSensorItem = new QTableWidgetItem();
    thermalEfficiencySensorItem = new QTableWidgetItem();
    airFuelRatioSensorItem = new QTableWidgetItem();
    motorSpeedSensorItem = new QTableWidgetItem();
    outputAirSpeedSensorItem = new QTableWidgetItem();
    vibrationSensorItem = new QTableWidgetItem();
    bodyTempSensorItem = new QTableWidgetItem();
    airTempSensorItem = new QTableWidgetItem();
    oilPressureItem = new QTableWidgetItem();
    oilTemperatureItem = new QTableWidgetItem();
    fuelFlowItem = new QTableWidgetItem();
    fuelItem = new QTableWidgetItem();
    egtItem = new QTableWidgetItem();
    torqueItem = new QTableWidgetItem();
    indicatedPowerItem = new QTableWidgetItem();
    frictionalPowerItem = new QTableWidgetItem();
    thermalEfficiencyItem = new QTableWidgetItem();
    airFuelRatioItem = new QTableWidgetItem();
    motorSpeedItem = new QTableWidgetItem();
    outputAirSpeedItem = new QTableWidgetItem();
    vibrationItem = new QTableWidgetItem();
    bodyTempItem = new QTableWidgetItem();
    airTempItem = new QTableWidgetItem();

    ui->sensorErrorTable->setItem(0, 1, oilPressureSensorItem);
    ui->sensorErrorTable->setItem(1, 1, oilTemperatureSensorItem);
    ui->sensorErrorTable->setItem(2, 1, fuelFlowSensorItem);
    ui->sensorErrorTable->setItem(3, 1, fuelSensorItem);
    ui->sensorErrorTable->setItem(4, 1, egtSensorItem);
    ui->sensorErrorTable->setItem(5, 1, torqueSensorItem);
    ui->sensorErrorTable->setItem(6, 1, indicatedPowerSensorItem);
    ui->sensorErrorTable->setItem(7, 1, frictionalPowerSensorItem);
    ui->sensorErrorTable->setItem(8, 1, thermalEfficiencySensorItem);
    ui->sensorErrorTable->setItem(9, 1, airFuelRatioSensorItem);
    ui->sensorErrorTable->setItem(10, 1, motorSpeedSensorItem);
    ui->sensorErrorTable->setItem(11, 1, outputAirSpeedSensorItem);
    ui->sensorErrorTable->setItem(12, 1, vibrationSensorItem);
    ui->sensorErrorTable->setItem(13, 1, bodyTempSensorItem);
    ui->sensorErrorTable->setItem(14, 1, airTempSensorItem);

    ui->sensorOtherTable->setItem(0, 1, oilPressureItem);
    ui->sensorOtherTable->setItem(1, 1, oilTemperatureItem);
    ui->sensorOtherTable->setItem(2, 1, fuelFlowItem);
    ui->sensorOtherTable->setItem(3, 1, fuelItem);
    ui->sensorOtherTable->setItem(4, 1, egtItem);
    ui->sensorOtherTable->setItem(5, 1, torqueItem);
    ui->sensorOtherTable->setItem(6, 1, indicatedPowerItem);
    ui->sensorOtherTable->setItem(7, 1, frictionalPowerItem);
    ui->sensorOtherTable->setItem(8, 1, thermalEfficiencyItem);
    ui->sensorOtherTable->setItem(9, 1, airFuelRatioItem);
    ui->sensorOtherTable->setItem(10, 1, motorSpeedItem);
    ui->sensorOtherTable->setItem(11, 1, outputAirSpeedItem);
    ui->sensorOtherTable->setItem(12, 1, vibrationItem);
    ui->sensorOtherTable->setItem(13, 1, bodyTempItem);
    ui->sensorOtherTable->setItem(14, 1, airTempItem);

    ui->sensorErrorTable->item(0, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(1, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(2, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(3, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(4, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(5, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(6, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(7, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(8, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(9, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(10, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(11, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(12, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(13, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorErrorTable->item(14, 1)->setTextAlignment(Qt::AlignCenter);

    ui->sensorOtherTable->item(0, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(1, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(2, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(3, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(4, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(5, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(6, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(7, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(8, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(9, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(10, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(11, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(12, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(13, 1)->setTextAlignment(Qt::AlignCenter);
    ui->sensorOtherTable->item(14, 1)->setTextAlignment(Qt::AlignCenter);
}

SensorErrorTable::~SensorErrorTable()
{
    delete ui;
}

void SensorErrorTable::setValue(QMap<char, float> map)
{
    // Update sensorErrorTable
    oilPressureSensorItem->setData(Qt::EditRole, map[char(OIL_PRESSURE_SENSOR_ERROR)]);
    oilTemperatureSensorItem->setData(Qt::EditRole, map[char(OIL_TEMPERATURE_SENSOR_ERROR)]);
    fuelFlowSensorItem->setData(Qt::EditRole, map[char(FUEL_FLOW_SENSOR_ERROR)]);
    fuelSensorItem->setData(Qt::EditRole, map[char(FUEL_SENSOR_ERROR)]);
    egtSensorItem->setData(Qt::EditRole, map[char(EGT_SENSOR_ERROR)]);
    torqueSensorItem->setData(Qt::EditRole, map[char(TORQUE_SENSOR_ERROR)]);
    indicatedPowerSensorItem->setData(Qt::EditRole, map[char(INDICATED_POWER_SENSOR_ERROR)]);
    frictionalPowerSensorItem->setData(Qt::EditRole, map[char(FRICTIONAL_POWER_SENSOR_ERROR)]);
    thermalEfficiencySensorItem->setData(Qt::EditRole, map[char(THERMAL_EFFICIENCY_SENSOR_ERROR)]);
    airFuelRatioSensorItem->setData(Qt::EditRole, map[char(AIR_FUEL_RATIO_SENSOR_ERROR)]);
    motorSpeedSensorItem->setData(Qt::EditRole, map[char(MOTOR_SPEED_SENSOR_ERROR)]);
    outputAirSpeedSensorItem->setData(Qt::EditRole, map[char(OUTPUT_AIR_SPEED_SENSOR_ERROR)]);
    vibrationSensorItem->setData(Qt::EditRole, map[char(VIBRATION_SENSOR_ERROR)]);
    bodyTempSensorItem->setData(Qt::EditRole, map[char(BODY_TEMP_SENSOR_ERROR)]);
    airTempSensorItem->setData(Qt::EditRole, map[char(AIR_TEMP_SENSOR_ERROR)]);

    ui->sensorErrorTable->setItemDelegateForColumn(2, delegate);

    // Update sensorOtherTable
    oilPressureItem->setData(Qt::EditRole, map[char(OIL_PRESSURE)]);
    oilTemperatureItem->setData(Qt::EditRole, map[char(OIL_TEMPERATURE)]);
    fuelFlowItem->setData(Qt::EditRole, map[char(FUEL_FLOW)]);
    fuelItem->setData(Qt::EditRole, map[char(FUEL)]);
    egtItem->setData(Qt::EditRole, map[char(EGT)]);
    torqueItem->setData(Qt::EditRole, map[char(TORQUE)]);
    indicatedPowerItem->setData(Qt::EditRole, map[char(INDICATED_POWER)]);
    frictionalPowerItem->setData(Qt::EditRole, map[char(FRICTIONAL_POWER)]);
    thermalEfficiencyItem->setData(Qt::EditRole, map[char(THERMAL_EFFICIENCY)]);
    airFuelRatioItem->setData(Qt::EditRole, map[char(AIR_FUEL_RATIO)]);
    motorSpeedItem->setData(Qt::EditRole, map[char(MOTOR_SPEED)]);
    outputAirSpeedItem->setData(Qt::EditRole, map[char(OUTPUT_AIR_SPEED)]);
    vibrationItem->setData(Qt::EditRole, map[char(VIBRATION)]);
    bodyTempItem->setData(Qt::EditRole, map[char(BODY_TEMP)]);
    airTempItem->setData(Qt::EditRole, map[char(AIR_TEMP)]);
}
