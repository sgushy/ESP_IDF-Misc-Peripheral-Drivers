///
/// ADS7828 driver definitions
///

#pragma once

#include <stddef.h>
#include <stdint.h>

#define ADS7828_CONV_FULL_ADDR(x) (x)      // Convert 0x20 etc. address to full based on datasheet

#define ADS7828_12_BIT_RESOLUTION 2
#define ADS7830_8_BIT_RESOLUTION 1

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct ads7828_config
    {
        int i2c_iface_num;
        int i2c_addr;
        int i2c_sda;
        int i2c_scl;
        int i2c_freq_hz;
        int data_bit_resolution; 
        int status;
    } ads7828_config_t;

    typedef struct ads7828_transaction
    {
        uint8_t command_byte;
        int receive_buffer;
    } __attribute__((packed)) ads7828_transaction_t;

#ifdef __cplusplus
}
#endif
