///
/// PCA9555 driver definitions
///

#pragma once

#include <stddef.h>
#include <stdint.h>

#define PCA9555_IO_MODE_OUTPUT 0
#define PCA9555_IO_MODE_INPUT 1

#define PCA9555_CMD_INPORT_0 0x00  // R byte: Input port 0
#define PCA9555_CMD_INPORT_1 0x01  // R byte: Input port 1
#define PCA9555_CMD_OUTPORT_0 0x02 // R/W: IO# 0-7
#define PCA9555_CMD_OUTPORT_1 0x03 // R/W: IO# 8-15
#define PCA9555_CMD_POLINV_0 0x04  //
#define PCA9555_CMD_POLINV_1 0x05
#define PCA9555_CMD_CONFPORT_0 0x06
#define PCA9555_CMD_CONFPORT_1 0x07

#define PCA9555_CONV_FULL_ADDR(x) (x)      // Convert 0x20 etc. address to full based on datasheet

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct pca9555_config
    {
        int i2c_iface_num;
        int i2c_addr;
        int i2c_sda;
        int i2c_scl;
        int i2c_freq_hz;
        int status;
    } pca9555_config_t;

    typedef struct pca9555_transaction
    {
        uint8_t command_byte_0;
        uint8_t payload_byte_0;
        uint8_t command_byte_1;
        uint8_t payload_byte_1;
    } __attribute__((packed)) pca9555_transaction_t;

#ifdef __cplusplus
}
#endif