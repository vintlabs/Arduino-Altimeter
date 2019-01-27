

/*
    MS5xxx.h - Library for accessing MS5xxx sensors via I2C
    Copyright (c) 2012 Roman Schmitz

    This file is part of arduino-ms5xxx.

    arduino-ms5xxx is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    arduino-ms5xxx is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with arduino-ms5xxx.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <Wire.h>
#include <math.h>
#include <MS5xxx.h>

#define USE_BLUETOOTH false  // set to false to cummunicate via seria port
#define MS5607_ADDRESS 0x76

MS5xxx sensor(&Wire);

// Set the reference pressure to the current pressure to get relative altitude changes
double pressure, temperature, p_ref, t_ref, altitude;
char receivedChar;
bool newData = false;

void setup() {
  Serial.begin(9600);
  sensor.setI2Caddr(MS5607_ADDRESS);
  if(sensor.connect()>0) {
    Serial.println("Error connecting...");
    delay(200);
    setup();
  }
  
  sensor.ReadProm();
  sensor.Readout();
  p_ref =  sensor.GetPres();
  t_ref = sensor.GetTemp() / 100.0f;

  //Serial.print( "Initial: ");
  //Serial.print(t_ref);
  //Serial.print( " " );
  //Serial.println( p_ref );
}

double getAltitude( double pres, double pres_ref, double temp )
{
  double a1 = pow( ( pres_ref / pres ), ( 1 / 5.257 ) );
  double a = (a1 - 1) * ( temp + 273.15 ) / 0.0065f;
  return a;
}


void recvOneChar() {
 if (Serial.available() > 0) {
 receivedChar = Serial.read();
 newData = true;
 //Serial.println(receivedChar);
 }
} 

void printJson()
{
  sensor.ReadProm();
  sensor.Readout();
  temperature = sensor.GetTemp() / 100.0f;
  pressure = sensor.GetPres();
  altitude = getAltitude( pressure, p_ref, temperature );
  
  Serial.print("{\"temp\": ");
  Serial.print(temperature);
  Serial.print(", \"pres\": ");
  Serial.print(pressure);
  Serial.print(", \"alt\": ");
  Serial.print(altitude);
  Serial.println("}");   
}

void printSerial()
{
  sensor.ReadProm();
  sensor.Readout();
  temperature = sensor.GetTemp() / 100.0f;
  pressure = sensor.GetPres();
  altitude = getAltitude( pressure, p_ref, temperature );

    Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("  Pres: ");
  Serial.print(pressure);
  Serial.print("  Alt: ");
  Serial.print( altitude );
  Serial.println("");
}

void loop() {
  
  if ( USE_BLUETOOTH )
  {  
    // Check for serial input
    recvOneChar();
  
    // if requested, get and send the reference pressure
    if( newData )
    {
      newData = false;
      switch (receivedChar)
      {
        case 'G':
          printJson();
          break;
      }
      if ( receivedChar == '0' )
      {
        //delay(2000);
        p_ref = sensor.GetPres();
        Serial.println( p_ref );
      }
    
    }
  }  // if USE_BLUETOOTH
  else
  {
    printSerial();
    delay(250);
  }
  
}

void test_crc() {
  sensor.ReadProm();
  sensor.Readout(); 
  Serial.print("CRC=0x");
  Serial.print(sensor.Calc_CRC4(), HEX);
    Serial.print(" (should be 0x");
  Serial.print(sensor.Read_CRC4(), HEX);
  Serial.print(")\n");
  Serial.print("Test Code CRC=0x");
  Serial.print(sensor.CRCcodeTest(), HEX);
  Serial.println(" (should be 0xB)");
}

