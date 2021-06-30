/*! 
    i2c(SDA, SCL)
*/


#include "mbed.h"
#include <cstdio>

// #define DEV_F0 1
// #define DEV_F7 1
// #define DEV_H7 1
#define DEV_G4 1
// #define DEV_L4 0
// #define DEV_L5 0

// #define I2C_2_DEV 1

uint32_t i2c_1_BaseAddr = 0x40005400;
uint32_t i2c_2_BaseAddr = 0x40005800;
uint8_t timingRegOffset = 0x10;
// I2C i2c_4(PC_7, PC_6);

uint32_t i2c_1_Tim_Reg = i2c_1_BaseAddr + timingRegOffset;
uint32_t i2c_2_Tim_Reg = i2c_2_BaseAddr + timingRegOffset;

#if ((defined (DEV_G4)) || (defined (DEV_L4)) ||\
     (defined (DEV_L5)))
uint32_t *i2c_1_TimVal = (uint32_t*)0x40005410;
uint32_t *i2c_2_TimVal = (uint32_t*)0x40005810;
#endif

#if defined (DEV_H7)
uint32_t *i2c_1_TimVal = (uint32_t*)0x40005410;
uint32_t *i2c_2_TimVal = (uint32_t*)0x40005810;
uint32_t *i2c_3_TimVal = (uint32_t*)0x40005C10;
uint32_t *i2c_4_TimVal = (uint32_t*)0x58001C10;
#endif

// main() runs in its own thread in the OS
int main()
{
printf("Test\n");
#if defined(DEV_F0)
    I2C i2c_1(PB_7, PB_6);
    #if defined(I2C_2_DEV)
        I2C i2c_2(PB_13, PB_14);
    #endif
#endif

#if defined(DEV_F7)
    I2C i2c_1(PB_9, PB_8);
    #if defined(I2C_2_DEV)
        I2C i2c_2(PB_13, PB_14);
    #endif
#endif

#if DEV_H7
    printf("I2C_1 Tim Val is 0x%x\n",i2c_4_TimVal[0]);
    I2C i2c_1(PD_13, PD_12);
    printf("I2C_1 Tim Val is 0x%x\n",i2c_4_TimVal[0]);
#if defined(I2C_2)
    I2C i2c_2(PA_8, PA_9);
#endif

#endif 

#if DEV_G4
    I2C i2c_1(PB_9, PB_8);
    // I2C i2c_2(PA_8, PA_9);
#endif

#if DEV_L4
    I2C i2c_1(PB_7, PB_8);
#if defined(I2C_2)
    I2C i2c_2(PA_8, PA_9);
#endif
#endif

#if DEV_L5
    I2C i2c_1(PB_7, PB_6);
#if defined(I2C_2)
    I2C i2c_2(PA_8, PA_9);
#endif
#endif
    // I2C i2c_3(PC_9, PC_8);
    Timer t;
    printf("start\n");
#if defined (DEV_H7)
    printf("I2C_1 Tim Val is 0x%x\n",i2c_4_TimVal[0]);
#endif
    i2c_1.frequency(1000000);
#if defined (DEV_H7)
    printf("I2C_1 Tim Val is 0x%x\n",i2c_4_TimVal[0]);
#endif
#if defined(I2C_2)
    printf("I2C_2 Tim Val is 0x%x\n",i2c_2_TimVal[0]);
    i2c_2.frequency(400000);
    printf("I2C_2 Tim Val is 0x%x\n",i2c_2_TimVal[0]);
#endif

    printf("\nI2C_1\n");
    for (int8_t address = 1; address < 127; address++) {
        t.start();

        if (i2c_1.write((address << 1), nullptr, 0, 0) == 0) {
            printf("0x%02X ACK\n", address);
            #if defined (DEV_H7)
            printf("I2C_1 Tim Val is 0x%x\n",i2c_4_TimVal[0]);
            #endif
            t.stop();
            // break;
        }

        t.stop();
        printf("I2C_1 Tim Val is 0x%x\n",i2c_1_TimVal[0]);
        // printf("address 0x%02X time: %lli\n\n", address , t.elapsed_time().count());
        t.reset();
    }
}
