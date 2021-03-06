#include "mcc_generated_files/mcc.h"
#include "i2c1_util.h"
#include "protocol.h"

#define delay __delay_us(100) // value larger than 1/100kHz (10 micro sec)

// I2C write
uint8_t i2c1_write(uint16_t dev_addr, uint8_t *pbuf, uint8_t len) {

    I2C1_MESSAGE_STATUS status;
    uint8_t write_status;
    delay;
    I2C1_MasterWrite(pbuf, len, dev_addr, &status);
    while (status == I2C1_MESSAGE_PENDING) {delay;};
    if (status == I2C1_MESSAGE_COMPLETE) {
        write_status = 0;
    } else {
        write_status = 1;
    }
    return write_status;
}

// I2C read
uint8_t i2c1_read(uint16_t dev_addr, uint8_t reg_addr, uint8_t *pbuf, uint8_t len) {

    uint8_t reg[1];
    I2C1_MESSAGE_STATUS status;
    uint8_t read_status;
    reg[0] = reg_addr;
    delay;
    I2C1_MasterWrite(reg, 1, dev_addr, &status);
    while (status == I2C1_MESSAGE_PENDING) {delay;};
    if (status == I2C1_MESSAGE_COMPLETE) {
        delay;
        I2C1_MasterRead(pbuf, len, dev_addr, &status); 
        while (status == I2C1_MESSAGE_PENDING) {delay;};
        if (status == I2C1_MESSAGE_COMPLETE) {
            read_status = 0;
        } else {
            read_status = 2;
        }
    } else {
        read_status = 1;
    }
    return read_status;
}

// I2C write w/o data
uint8_t i2c1_write_no_data(uint16_t dev_addr, uint8_t reg_addr) {

    uint8_t buf[1];
    I2C1_MESSAGE_STATUS status;
    uint8_t write_status;
    buf[0] = reg_addr;
    delay;
    I2C1_MasterWrite(buf, 1, dev_addr, &status);
    while (status == I2C1_MESSAGE_PENDING) {delay;};
    if (status == I2C1_MESSAGE_COMPLETE) {
        write_status = 0;
    } else {
        write_status = 1;
    }
    return write_status;
}
