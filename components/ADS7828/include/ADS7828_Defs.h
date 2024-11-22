///
/// ADS7828 driver definitions
///

#pragma once

#include <stddef.h>
#include <stdint.h>

#define ADS7828_CONV_FULL_ADDR(x) (x)      // Convert 0x20 etc. address to full based on datasheet

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
        int status;
    } ads7828_config_t;

    typedef struct ads7828_transaction
    {
        uint8_t command_byte_0;
        uint8_t payload_byte_0;
        uint8_t command_byte_1;
        uint8_t payload_byte_1;
    } __attribute__((packed)) ads7828_transaction_t;

#ifdef __cplusplus
}
#endif