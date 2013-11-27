
#include <Arduino.h> 
#include <Wire.h>
#include "L3G4200D.h"

L3G4200D::L3G4200D()
{
  
}

void L3G4200D::setupL3G4200D(int scale){
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  byte data = 0b00001111;
  writeRegister(L3G4200D_Address, CTRL_REG1, &data);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  data = 0b00000000;
  writeRegister(L3G4200D_Address, CTRL_REG2, &data);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  data = 0b00001000;
  writeRegister(L3G4200D_Address, CTRL_REG3, &data);

  // CTRL_REG4 controls the full-scale range, among other things:

  if(scale == 250){
    data = 0b00000000;
    writeRegister(L3G4200D_Address, CTRL_REG4, &data);
  }else if(scale == 500){
    data = 0b00010000;
    writeRegister(L3G4200D_Address, CTRL_REG4, &data);
  }else{
    data = 0b00110000;
    writeRegister(L3G4200D_Address, CTRL_REG4, &data);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  data = 0b00000000;
  writeRegister(L3G4200D_Address, CTRL_REG5, &data);
}


int L3G4200D::writeRegister(int deviceAddress, byte regAddress, byte *val) {
    int writtenBytes;
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(regAddress);       // send register address
    writtenBytes = Wire.write(val, 1);         // send value to write
    Wire.endTransmission();     // end transmission
    return writtenBytes;
}

int L3G4200D::readRegister(int deviceAddress, byte reg_addr, int nbytes, byte *buffer)
{
	int idx = 0;

	Wire.beginTransmission(deviceAddress);
	Wire.write(reg_addr);
	Wire.endTransmission(); 
	
	Wire.requestFrom(deviceAddress, nbytes);

	while(Wire.available() && idx < nbytes)
	{ 
		buffer[idx++] = Wire.read();
	}
	
	return idx;
}

int L3G4200D::readRegister(int deviceAddress, byte address){
    byte buffer;
    readRegister(deviceAddress, address, 1, &buffer);
    return (int)buffer;
}

void L3G4200D::read(int *x, int *y, int *z){
  byte xMSB = readRegister(L3G4200D_Address, 0x29);
  byte xLSB = readRegister(L3G4200D_Address, 0x28);
  *x = ((xMSB << 8) | xLSB);

  byte yMSB = readRegister(L3G4200D_Address, 0x2B);
  byte yLSB = readRegister(L3G4200D_Address, 0x2A);
  *y = ((yMSB << 8) | yLSB);

  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  *z = ((zMSB << 8) | zLSB);
}
