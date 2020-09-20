#include <Arduino.h>
#include "MPU6050.h"

namespace ArduForge{
    MPU6050::MPU6050(void){
        m_SensorAdr = 0x68;
        m_pWire = &Wire;
    }//Constructor

    MPU6050::~MPU6050(void){

    }//Destructor

    void MPU6050::begin(TwoWire *pWire, int16_t Adr, AccelConfig AC, GyroConfig GC){
        m_SensorAdr = Adr;
        m_pWire = pWire;
        wake();
        accelSensivity(AC);
        gyroSensivity(GC);
        calibrate();
    }//initialize

    void MPU6050::end(void){
        m_pWire = &Wire;
        m_SensorAdr = 0x68;
        m_GyroConfig = GyroConfig::SCALE_250;
        m_AccelConfig = AccelConfig::SCALE_2G;
    }//clear

    MPU6050::RawSensorData MPU6050::readRaw(void){
        RawSensorData Rval;
        m_pWire->beginTransmission(m_SensorAdr);
        m_pWire->write(0x3B); // register ACCEL_XOUT_H
        m_pWire->endTransmission(false); 
        m_pWire->requestFrom(m_SensorAdr, 7*2, 1); // request a total for 7*2 = 14 registers containing the sensor sensor data 
        Rval.AccelX = m_pWire->read() << 8 | m_pWire->read();
        Rval.AccelY = m_pWire->read() << 8 | m_pWire->read();
        Rval.AccelZ = m_pWire->read() << 8 | m_pWire->read();
        Rval.Temperature = (m_pWire->read() << 8 | m_pWire->read());
        Rval.GyroX = m_pWire->read() << 8 | m_pWire->read();
        Rval.GyroY = m_pWire->read() << 8 | m_pWire->read();
        Rval.GyroZ = m_pWire->read() << 8 | m_pWire->read();
        Wire.endTransmission();
        return Rval;
    }//readRaw


    MPU6050::SensorData MPU6050::read(void){
        const float AccelSens = accelSensivity(m_AccelConfig);
        const float GyroSens = gyroSensivity(m_GyroConfig);
        const RawSensorData Data = readRaw();
        SensorData Rval;
        Rval.AccelX = (Data.AccelX - m_Calibration.AccelX)/ AccelSens;
        Rval.AccelY = (Data.AccelY - m_Calibration.AccelY)/ AccelSens;
        Rval.AccelZ = (Data.AccelZ - m_Calibration.AccelZ)/ AccelSens;
        Rval.GyroX = (Data.GyroX - m_Calibration.GyroX) / GyroSens;
        Rval.GyroY = (Data.GyroY - m_Calibration.GyroY) / GyroSens;
        Rval.GyroZ = (Data.GyroZ - m_Calibration.GyroZ) / GyroSens;
        Rval.Temperature = Data.Temperature / 340.0 + 36.53;
        return Rval;
    }//read

    void MPU6050::configAccel(AccelConfig Value){
        m_pWire->beginTransmission(m_SensorAdr);
        m_pWire->write(0x1C);
        int8_t Reg = 0;
        switch(Value){
            case AccelConfig::SCALE_2G: Reg = 0b00000000; break;
            case AccelConfig::SCALE_4G: Reg = 0b00001000; break;
            case AccelConfig::SCALE_8G:Reg = 0b00010000; break;
            case AccelConfig::SCALE_16G: Reg = 0b00011000; break;
            default: break;
        }
        m_pWire->write(Reg);
        m_pWire->endTransmission();
        m_AccelConfig = Value;
    }//configAccel

    void MPU6050::configGyro(GyroConfig Value){
        m_pWire->beginTransmission(m_SensorAdr);
        m_pWire->write(0x1B);
        int8_t Reg = 0;
        switch(Value){
            case GyroConfig::SCALE_250: Reg = 0b00000000; break;
            case GyroConfig::SCALE_500: Reg = 0b00001000; break;
            case GyroConfig::SCALE_1000: Reg = 0b00010000; break;
            case GyroConfig::SCALE_2000: Reg = 0b00011000; break;
            default: break;
        }
        m_pWire->write(Reg);
        m_pWire->endTransmission();
        m_GyroConfig = Value;
    }//configGyro

    void MPU6050::configThermistor(bool Enable){      
        int8_t Reg = readRegister(0x6B);
         m_pWire->beginTransmission(m_SensorAdr);
        if(Enable) Reg &= 0b11110111;
        else Reg |= 0b00001000;
        m_pWire->write(0x6B);
        m_pWire->write(Reg);
        m_pWire->endTransmission(); 
    }//configThermistor


    void MPU6050::sleep(void){
       int8_t Reg = readRegister(0x6B);
       m_pWire->beginTransmission(m_SensorAdr);
       m_pWire->write(0x6B);
       m_pWire->write(Reg | 0b01000000);
       m_pWire->endTransmission();
    }//sleep

    void MPU6050::wake(void){
        int8_t Reg = readRegister(0x6B);
        m_pWire->beginTransmission(m_SensorAdr);
        m_pWire->write(0x6B);
        m_pWire->write(Reg & 0b10111111);
        m_pWire->endTransmission();
    }//wake

    int16_t MPU6050::accelSensivity(AccelConfig Value){
        int16_t Rval = 1;
        switch(Value){
            case AccelConfig::SCALE_2G: Rval = 16384; break;
            case AccelConfig::SCALE_4G: Rval = 8192; break;
            case AccelConfig::SCALE_8G: Rval = 4096; break;
            case AccelConfig::SCALE_16G: Rval = 2048; break;
            default: Rval = 16384; break;
        }
        return Rval;
    }//accelSensivity

    float MPU6050::gyroSensivity(GyroConfig Value){
        float Rval = 1;
        switch(Value){
            case GyroConfig::SCALE_250: Rval = 131; break;
            case GyroConfig::SCALE_500: Rval = 62.5; break;
            case GyroConfig::SCALE_1000: Rval = 32.6; break;
            case GyroConfig::SCALE_2000: Rval = 16.4; break;
            default: Rval = 131; break;
        }
        return Rval;
    }//gyroSensivity

    int8_t MPU6050::readRegister(int8_t Reg){
        m_pWire->beginTransmission(m_SensorAdr);
        m_pWire->write(Reg);
        m_pWire->endTransmission(false);
        m_pWire->requestFrom(m_SensorAdr, 1);
        int8_t Rval = m_pWire->read();
        m_pWire->endTransmission();
        return Rval;
    }//readRegister

    void MPU6050::calibrate(void){
        m_Calibration = readRaw();
    }//calibrate
}//name-space