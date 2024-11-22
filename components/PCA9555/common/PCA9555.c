///
/// PCA9555 driver
///

#include "PCA9555.h"
#include "PCA9555_Interfaces.h"

// The status of the I2C bus
int i2c_bus_status = -1; 

/// @brief Start the I2C communication with PCA9555, if not already started
/// @param pca9555_handle The PCA9555 config structure
/// @return 0 on success
int pca9555_init(const pca9555_config_t *pca9555_handle)
{
    if(pca9555_handle == NULL || pca9555_handle->i2c_addr == 0)
    {
        return -1;
    }
    i2c_bus_status = 0;
    return i2c_bus_status;
}

/// @brief Send transaction to PCA9555, this is usually called at the end of each cycle, after toggling all required IOs with pca9555_toggle_io()
/// @param pca9555_handle The PCA9555 config structure
/// @param send_buffer The pca9555_transaction_t structure which stores the required pin states
/// @return 
int pca9555_update_outputs(const pca9555_config_t *pca9555_handle, pca9555_transaction_t *send_buffer)
{
    if(i2c_bus_status < 0)
    {
        return i2c_bus_status;
    }

    send_buffer->command_byte_0 = PCA9555_CMD_OUTPORT_0;
    send_buffer->command_byte_1 = PCA9555_CMD_OUTPORT_1;

    int status = pca9555_i2c_send(pca9555_handle->i2c_iface_num, PCA9555_CONV_FULL_ADDR(pca9555_handle->i2c_addr), &send_buffer->command_byte_0, 2);
    status |= pca9555_i2c_send(pca9555_handle->i2c_iface_num, PCA9555_CONV_FULL_ADDR(pca9555_handle->i2c_addr), &send_buffer->command_byte_1, 2);
    return status;
}

/// @brief Send transaction to PCA9555, this is usually called at the end of each cycle, after toggling all required IOs with pca9555_toggle_io()
/// @param pca9555_handle The PCA9555 config structure
/// @param send_buffer The pca9555_transaction_t structure which stores the required pin states
/// @return 
int pca9555_config_io_banks(const pca9555_config_t *pca9555_handle, pca9555_transaction_t *send_buffer)
{
    if(i2c_bus_status < 0)
    {
        return i2c_bus_status;
    }

    send_buffer->command_byte_0 = PCA9555_CMD_CONFPORT_0;
    send_buffer->command_byte_1 = PCA9555_CMD_CONFPORT_1;

    int status = pca9555_i2c_send(pca9555_handle->i2c_iface_num, PCA9555_CONV_FULL_ADDR(pca9555_handle->i2c_addr), &send_buffer->command_byte_0, 2);
    status |= pca9555_i2c_send(pca9555_handle->i2c_iface_num, PCA9555_CONV_FULL_ADDR(pca9555_handle->i2c_addr), &send_buffer->command_byte_1, 2);
    return status;
}

/// @brief For now, unused...
/// @param pca9555_handle 
/// @param send_buffer 
/// @param timeout_ticks 
/// @return 
int pca9555_receive_message(pca9555_config_t *pca9555_handle, pca9555_transaction_t *send_buffer, int timeout_ticks)
{
    if(i2c_bus_status < 0)
    {
        return i2c_bus_status;
    }
    // return pca9555_i2c_receive(pca9555_handle->i2c_addr, send_buffer, sizeof(pca9555_transaction_t));
    return -1;
}

/// @brief Toggle the indicated PCA9555 IO state, but does not send the transaction.
/// @param pca9555_handle The PCA9555 device
/// @param send_buffer 
/// @param io_num 0 - 15 corresponding to the physical pins
/// @param state -1 = off, 1 = on, 0 = do not change
/// @return 0 on success, -1 on invalid io_num, -2 on null parameters
int pca9555_toggle_output(const pca9555_config_t *pca9555_handle, pca9555_transaction_t* send_buffer, int io_num, int state)
{
    if (pca9555_handle == NULL || send_buffer == NULL)
    {
        return -2; // Null parameters
    }
    if (io_num < 0 || io_num > 15)
    {
        return -1; // Invalid IO number
    }

    uint8_t bitmask = 1 << (io_num % 8);

    if (state == -1)
    {
        if (io_num < 8)
        {
            send_buffer->payload_byte_0 &= ~bitmask; // Clear bit (set to 0)
        }
        else
        {
            send_buffer->payload_byte_1 &= ~bitmask; // Clear bit (set to 0)
        }
    }
    else if (state == 1)
    {
        if (io_num < 8)
        {
            send_buffer->payload_byte_0 |= bitmask; // Set bit to 1
        }
        else
        {
            send_buffer->payload_byte_1 |= bitmask; // Set bit to 1
        }
    }
    // If state is 0, do nothing

    return 0;
}
