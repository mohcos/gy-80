#define L3G4200D_Address 105 //I2C address of the L3G4200D
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24

class L3G4200D
{
    public:
     L3G4200D();
     void setupL3G4200D(int scale);
     int writeRegister(int deviceAddress, byte regAddress, byte *val);
     int readRegister(int deviceAddress, byte address);
     int readRegister(int deviceAddress, byte reg_addr, int nbytes, byte *buffer);
     void read(int *x, int *y, int *z);
};
