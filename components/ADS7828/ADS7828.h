///
/// Driver for ADS7828 8-channel ADC
///

#pragma once

#include "ADS7828_Defs.h"

#ifdef __cplusplus
extern "C"
{
#endif

int ads7828_init(const ads7828_config_t *ads7828_handle);
int ads7830_init(const ads7828_config_t *ads7828_handle);

int ads7828_read_channel_16(const ads7828_config_t *ads7828_handle, int channel_num, uint16_t *buffer);
int ads7830_read_channel_8(const ads7828_config_t *ads7828_handle, int channel_num, uint8_t *buffer);

#ifdef __cplusplus
}
#endif
