#include "process_message.h"

#include <QDebug>
#include <windows.h>
#include <unistd.h>
#include <QThread>

Process_message::Process_message()
{
    this->MSG_counter = -1;

    flag[char(OIL_PRESSURE)]        = 0;
    flag[char(OIL_TEMPERATURE)]     = 0;
    flag[char(FUEL_FLOW)]           = 0;
    flag[char(FUEL)]                = 0;
    flag[char(EGT)]                 = 0;
    flag[char(TORQUE)]              = 0;
    flag[char(INDICATED_POWER)]     = 0;
    flag[char(FRICTIONAL_POWER)]    = 0;
    flag[char(THERMAL_EFFICIENCY)]  = 0;
    flag[char(AIR_FUEL_RATIO)]      = 0;
    flag[char(MOTOR_SPEED)]         = 0;
    flag[char(OUTPUT_AIR_SPEED)]    = 0;
    flag[char(VIBRATION)]           = 0;
    flag[char(BODY_TEMP)]           = 0;
    flag[char(AIR_TEMP)]            = 0;

    flag[char(OIL_PRESSURE_SENSOR_ERROR)]        = 0;
    flag[char(OIL_TEMPERATURE_SENSOR_ERROR)]     = 0;
    flag[char(FUEL_FLOW_SENSOR_ERROR)]           = 0;
    flag[char(FUEL_SENSOR_ERROR)]                = 0;
    flag[char(EGT_SENSOR_ERROR)]                 = 0;
    flag[char(TORQUE_SENSOR_ERROR)]              = 0;
    flag[char(INDICATED_POWER_SENSOR_ERROR)]     = 0;
    flag[char(FRICTIONAL_POWER_SENSOR_ERROR)]    = 0;
    flag[char(THERMAL_EFFICIENCY_SENSOR_ERROR)]  = 0;
    flag[char(AIR_FUEL_RATIO_SENSOR_ERROR)]      = 0;
    flag[char(MOTOR_SPEED_SENSOR_ERROR)]         = 0;
    flag[char(OUTPUT_AIR_SPEED_SENSOR_ERROR)]    = 0;
    flag[char(VIBRATION_SENSOR_ERROR)]           = 0;
    flag[char(BODY_TEMP_SENSOR_ERROR)]           = 0;
    flag[char(AIR_TEMP_SENSOR_ERROR)]            = 0;
}

void Process_message::setRawData(QByteArray data)
{
    this->rawData = data;
}

QMap<char,float> Process_message::getFlags()
{
    return this->flag;
}

void Process_message::processData()
{
    m_mtx.lock();

    qDebug() << "inside";

    int index = 0;
    uint16_t sum = 0;
    uint16_t checksum = 0;
    uint8_t ID_Number = 0;
    uint32_t data = 0;
    uint32_t factor = 0;
    float real_data;
    QMap<char,float> received_data;

    for( ; index < 4 ; index++){
        if(rawData[index] != char(HEADER_VALUE)){
            m_mtx.unlock();
            qDebug() << "header";
            return;
        }
    }

    if(MSG_counter == uint8_t(rawData[index])){
        m_mtx.unlock();
        qDebug() << "msg_counter";
        return;
    }
    else{
        sum += rawData[index];
        MSG_counter = uint8_t(rawData[index++]);
    }

    sum += rawData[index];
    ID_Number = uint8_t(rawData[index++]);

    if(rawData[18 + (ID_Number - 1) * 10] != char(FOOTER_VALUE)){
        m_mtx.unlock();
        qDebug() << "footer";
        return;
    }

    while(index <= 15 + (ID_Number - 1) * 10){

        if(rawData[index] == char(OIL_PRESSURE)){
            qDebug() << "OIL_PRESSURE";
            sum += uint8_t(rawData[index] & 0x00FF);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1000){
                    received_data[char(OIL_PRESSURE)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(OIL_TEMPERATURE)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 400){
                    received_data[char(OIL_TEMPERATURE)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(FUEL_FLOW)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 800){
                    received_data[char(FUEL_FLOW)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(FUEL)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 800){
                    received_data[char(FUEL)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(EGT)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 400){
                    received_data[char(EGT)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(TORQUE)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 400){
                    received_data[char(TORQUE)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(INDICATED_POWER)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 400){
                    received_data[char(INDICATED_POWER)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(FRICTIONAL_POWER)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 400){
                    received_data[char(FRICTIONAL_POWER)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(THERMAL_EFFICIENCY)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 100){
                    received_data[char(THERMAL_EFFICIENCY)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(AIR_FUEL_RATIO)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                float real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 20){
                    received_data[char(AIR_FUEL_RATIO)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(MOTOR_SPEED)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1000){
                    received_data[char(MOTOR_SPEED)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(OUTPUT_AIR_SPEED)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1000){
                    received_data[char(OUTPUT_AIR_SPEED)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(VIBRATION)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 100){
                    received_data[char(VIBRATION)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(BODY_TEMP)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 400){
                    received_data[char(BODY_TEMP)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(AIR_TEMP)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 400){
                    received_data[char(AIR_TEMP)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(OIL_PRESSURE_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(OIL_PRESSURE_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(OIL_TEMPERATURE_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(OIL_TEMPERATURE_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(FUEL_FLOW_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(FUEL_FLOW_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(FUEL_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(FUEL_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(EGT_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(EGT_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(TORQUE_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(TORQUE_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(INDICATED_POWER_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(INDICATED_POWER_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(FRICTIONAL_POWER_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(FRICTIONAL_POWER_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(THERMAL_EFFICIENCY_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(THERMAL_EFFICIENCY_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(AIR_FUEL_RATIO_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(AIR_FUEL_RATIO_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(MOTOR_SPEED_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(MOTOR_SPEED_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(OUTPUT_AIR_SPEED_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(OUTPUT_AIR_SPEED_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(VIBRATION_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(VIBRATION_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(BODY_TEMP_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(BODY_TEMP_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else if(rawData[index] == char(AIR_TEMP_SENSOR_ERROR)){
            sum += uint16_t(rawData[index]);
            index += 2;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &data);
            sum += data;
            index += 4;
            packData32(rawData[index], rawData[index + 1], rawData[index + 2], rawData[index + 3], &factor);
            sum += factor;
            index += 4;
            if(factor != 0){
                real_data = static_cast<float>(data) / factor;
                if(real_data >= 0 && real_data <= 1){
                    received_data[char(AIR_TEMP_SENSOR_ERROR)] = real_data;
                }
            }
        }

        else{
            index += 10;
        }
    }

    packData16(rawData[index], rawData[index + 1], &checksum);
    if(checksum == sum){
        for (auto it = received_data.begin(); it != received_data.end(); ++it) {
            flag[it.key()] = it.value();
            qDebug() << it.value();
        }
        emit updateGauge();
        emit updatePlot();
    }
    else {
        qDebug() << "checksum";
    }

    m_mtx.unlock();
}

void Process_message::packData32(char byte1, char byte2, char byte3, char byte4, uint32_t *data)
{
    uint32_t packedData = uint32_t((byte1 & 0x00FF) + ((byte2 & 0x00FF) << 8) + ((byte3 & 0x00FF) << 16) + ((byte4 & 0x00FF) << 24));
    *data = packedData;
}

void Process_message::packData16(char byte1, char byte2, uint16_t *data)
{
    uint16_t packedData = (byte1 & 0x00FF) + ((byte2 & 0x00FF) << 8);
    *data = packedData;
}



