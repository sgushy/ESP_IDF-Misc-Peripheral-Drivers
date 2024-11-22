///
/// Driver for PCA9555 16-channel I/O expander
///

#pragma once

#include "PCA9555_Defs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    
    int pca9555_init(const pca9555_config_t *pca9555_handle);

    int pca9555_toggle_output(const pca9555_config_t *pca9555_handle, pca9555_transaction_t* send_buffer, int io_num, int state);
    int pca9555_update_outputs(const pca9555_config_t *pca9555_handle, pca9555_transaction_t* send_buffer);

    int pca9555_receive_message(pca9555_config_t *pca9555_handle, pca9555_transaction_t* send_buffer, int timeout_ticks);

    int pca9555_config_io_banks(const pca9555_config_t *pca9555_handle, pca9555_transaction_t* send_buffer);
#ifdef __cplusplus
}
#endif