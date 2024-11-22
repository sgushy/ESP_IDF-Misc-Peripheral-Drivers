///
/// ADS7828 driver
///

#include "ADS7828.h"
#include "ADS7828_Interfaces.h"

// The status of the I2C bus
int i2c_bus_status = -1; 

/// @brief Start the I2C communication with ADS7828, if not already started
/// @param ads7828_handle The ADS7828 config structure
/// @return 0 on success
int ads7828_init(const ads7828_config_t *ads7828_handle)
{
    if(ads7828_handle == NULL || ads7828_handle->i2c_addr == 0)
    {
        return -1;
    }
    i2c_bus_status = 0;
    return i2c_bus_status;
}

/// @brief Send transaction to ADS7828, this is usually called at the end of each cycle, after toggling all required IOs with ads7828_toggle_io()
/// @param ads7828_handle The ADS7828 config structure
/// @param send_buffer The ads7828_transaction_t structure which stores the required pin states
/// @return 
int ads7828_update_outputs(const ads7828_config_t *ads7828_handle, ads7828_transaction_t *send_buffer)
{
    if(i2c_bus_status < 0)
    {
        return i2c_bus_status;
    }

    // send_buffer->command_byte_0 = ADS7828_CMD_OUTPORT_0;
    // send_buffer->command_byte_1 = ADS7828_CMD_OUTPORT_1;

    int status = ads7828_i2c_send(ads7828_handle->i2c_iface_num, ADS7828_CONV_FULL_ADDR(ads7828_handle->i2c_addr), &send_buffer->command_byte_0, 2);
    status |= ads7828_i2c_send(ads7828_handle->i2c_iface_num, ADS7828_CONV_FULL_ADDR(ads7828_handle->i2c_addr), &send_buffer->command_byte_1, 2);
    return status;
}

/// @brief Send transaction to ADS7828, this is usually called at the end of each cycle, after toggling all required IOs with ads7828_toggle_io()
/// @param ads7828_handle The ADS7828 config structure
/// @param send_buffer The ads7828_transaction_t structure which stores the required pin states
/// @return 
int ads7828_config_io_banks(const ads7828_config_t *ads7828_handle, ads7828_transaction_t *send_buffer)
{
    if(i2c_bus_status < 0)
    {
        return i2c_bus_status;
    }

    // send_buffer->command_byte_0 = ADS7828_CMD_CONFPORT_0;
    // send_buffer->command_byte_1 = ADS7828_CMD_CONFPORT_1;

    int status = ads7828_i2c_send(ads7828_handle->i2c_iface_num, ADS7828_CONV_FULL_ADDR(ads7828_handle->i2c_addr), &send_buffer->command_byte_0, 2);
    status |= ads7828_i2c_send(ads7828_handle->i2c_iface_num, ADS7828_CONV_FULL_ADDR(ads7828_handle->i2c_addr), &send_buffer->command_byte_1, 2);
    return status;
}

/// @brief For now, unused...
/// @param ads7828_handle 
/// @param send_buffer 
/// @param timeout_ticks 
/// @return 
int ads7828_receive_message(ads7828_config_t *ads7828_handle, ads7828_transaction_t *send_buffer, int timeout_ticks)
{
    if(i2c_bus_status < 0)
    {
        return i2c_bus_status;
    }
    // return ads7828_i2c_receive(ads7828_handle->i2c_addr, send_buffer, sizeof(ads7828_transaction_t));
    return -1;
}

/// @brief Toggle the indicated ADS7828 IO state, but does not send the transaction.
/// @param ads7828_handle The ADS7828 device
/// @param send_buffer 
/// @param io_num 0 - 15 corresponding to the physical pins
/// @param state -1 = off, 1 = on, 0 = do not change
/// @return 0 on success, -1 on invalid io_num, -2 on null parameters
int ads7828_toggle_output(const ads7828_config_t *ads7828_handle, ads7828_transaction_t* send_buffer, int io_num, int state)
{
    if (ads7828_handle == NULL || send_buffer == NULL)
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
