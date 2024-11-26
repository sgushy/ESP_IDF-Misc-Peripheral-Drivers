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

int ads7828_read_channel(const ads7828_config_t *ads7828_handle, ads7828_transaction_t *ads7828_transaction, int *buffer);

#ifdef __cplusplus
}
#endif
