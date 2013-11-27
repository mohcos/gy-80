# include <Arduino.h>
#define BMP085_ADDRESS 0x77  // I2C address of BMP085

const byte OSS = 0;  // Oversampling Setting

class BMP085 {
  public:
    BMP085();
    void bmp085Calibration();
    float bmp085GetTemperature();
    long bmp085GetPressure();
    float calcAltitude(float pressure);
  private:
    char bmp085Read(byte address);
    int bmp085ReadInt(byte address);
    unsigned int bmp085ReadUT();
    unsigned long bmp085ReadUP();
    void writeRegister(int deviceAddress, byte address, byte val);
    int readRegister(byte reg_addr, int nbytes, byte *buffer);
};
