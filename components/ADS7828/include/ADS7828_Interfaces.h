///
/// ADS7828 driver interface layer
///

#pragma once

#include "ADS7828_Defs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    int ads7828_i2c_send(int i2c_num, int i2c_addr, const void *data, size_t len);
    int ads7828_i2c_receive(int i2c_addr, void *data_buffer, size_t len);

    int ads7828_log(const char *format, ...);

#ifdef __cplusplus
}
#endif