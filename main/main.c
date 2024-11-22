
#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_console.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "PCA9555.h"
#include "ADS7828.h"

#define PCA9555_I2C I2C_NUM_0
#define PCA9555_SDA 21
#define PCA9555_SCL 26

static const char *TAG = "PCA-9555 IO-Test";

// PCA9555 I/O expander unit 0
pca9555_config_t pca9555_0;
pca9555_transaction_t pca9555_0_io_mode_conf;         // Use this to set I/O direction
pca9555_transaction_t pca9555_0_polarity_invert_conf; // Use this to configure I/O polarity inversion, this is not usually used
pca9555_transaction_t pca9555_0_output_register;      // Use this to set output levels, only works for pins with IO direction set to output
pca9555_transaction_t pca9555_0_input_register;       // Use this to get input levels, only works for pins with IO direction set to input

/// @brief Start I2C bus with the given config
/// @param config
/// @return 0 if successful, -1 if failed
int i2c_start()
{
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = PCA9555_SDA,
        .scl_io_num = PCA9555_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
    };
    esp_err_t err = i2c_param_config(PCA9555_I2C, &i2c_config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "I2C param config failed: %s", esp_err_to_name(err));
        return -1;
    }
    err = i2c_driver_install(PCA9555_I2C, I2C_MODE_MASTER, 0, 0, 0);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "I2C driver install failed: %s", esp_err_to_name(err));
        return -1;
    }
    return 0;
}

/// @brief Simple test, ripple through the
void pca_9555_0_iotest()
{
    memset(&pca9555_0_output_register, 0, sizeof(pca9555_transaction_t));
    memset(&pca9555_0_io_mode_conf, 0, sizeof(pca9555_transaction_t));

    int status0, status1 = 0;

    // Set all IO banks to 0 (output) mode
    pca9555_0_io_mode_conf.payload_byte_0 = PCA9555_IO_MODE_OUTPUT;
    pca9555_0_io_mode_conf.payload_byte_1 = PCA9555_IO_MODE_OUTPUT;
    status0 = pca9555_config_io_banks(&pca9555_0, &pca9555_0_io_mode_conf);

    if (status0 != 0 || status1 != 0)
    {
        ESP_LOGE(TAG, "Error occurred while configuring PCA9555 IO! Toggle %d, Send %d", status0, status1);
    }

    ESP_LOGI(TAG, "Turning all outputs on!");
    for (int i = 0; i < 16; i++)
    {
        status0 = pca9555_toggle_output(&pca9555_0, &pca9555_0_output_register, i, 1);
        status1 = pca9555_update_outputs(&pca9555_0, &pca9555_0_output_register);
        if (status0 != 0 || status1 != 0)
        {
            ESP_LOGE(TAG, "Error occurred while toggling PCA9555 IO! Toggle %d, Send %d", status0, status1);
        }
        ESP_LOGI(TAG, "IO status register 0: %hhu, 1:%hhu", pca9555_0_output_register.payload_byte_0, pca9555_0_output_register.payload_byte_1);
        vTaskDelay(100);
    }

    ESP_LOGI(TAG, "Turning all outputs off!");
    for (int i = 0; i < 16; i++)
    {
        status0 = pca9555_toggle_output(&pca9555_0, &pca9555_0_output_register, i, -1);
        status1 = pca9555_update_outputs(&pca9555_0, &pca9555_0_output_register);
        if (status0 != 0 || status1 != 0)
        {
            ESP_LOGE(TAG, "Error occurred while toggling PCA9555 IO! Toggle %d, Send %d", status0, status1);
        }
        ESP_LOGI(TAG, "IO status register 0: %hhu, 1:%hhu", pca9555_0_output_register.payload_byte_0, pca9555_0_output_register.payload_byte_1);
        vTaskDelay(100);
    }
}

void pca_9555_0_set_all_outputs_low()
{
    memset(&pca9555_0_io_mode_conf, 0, sizeof(pca9555_transaction_t));
    int status0, status1 = 0;

    // Set all IO banks to 0 (output) mode
    pca9555_0_io_mode_conf.payload_byte_0 = PCA9555_IO_MODE_OUTPUT;
    pca9555_0_io_mode_conf.payload_byte_1 = PCA9555_IO_MODE_OUTPUT;
    status0 = pca9555_config_io_banks(&pca9555_0, &pca9555_0_io_mode_conf);

    memset(&pca9555_0_output_register, 0, sizeof(pca9555_transaction_t));
    status1 = pca9555_update_outputs(&pca9555_0, &pca9555_0_output_register);
}

void pca_9555_0_set_all_outputs_high()
{
    memset(&pca9555_0_io_mode_conf, 0, sizeof(pca9555_transaction_t));
    int status0, status1 = 0;

    // Set all IO banks to 0 (output) mode
    pca9555_0_io_mode_conf.payload_byte_0 = PCA9555_IO_MODE_OUTPUT;
    pca9555_0_io_mode_conf.payload_byte_1 = PCA9555_IO_MODE_OUTPUT;
    status0 = pca9555_config_io_banks(&pca9555_0, &pca9555_0_io_mode_conf);

    memset(&pca9555_0_output_register, 0xFF, sizeof(pca9555_transaction_t));
    status1 = pca9555_update_outputs(&pca9555_0, &pca9555_0_output_register);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Started...");

    if (i2c_start() != 0)
    {
        return;
    }

    ESP_LOGI(TAG, "Initialized I2C!");

    pca9555_0.i2c_addr = 0x20;
    pca9555_0.i2c_freq_hz = 400000;
    pca9555_0.i2c_iface_num = PCA9555_I2C;
    pca9555_0.i2c_sda = PCA9555_SDA;
    pca9555_0.i2c_scl = PCA9555_SCL;
    pca9555_0.status = -1;

    if (pca9555_init(&pca9555_0) != 0)
    {
        ESP_LOGE(TAG, "Error starting PCA9555!");
    }
    else
    {
        ESP_LOGI(TAG, "Successful start PCA9555!");
    }

    for (int i = 0; i < 5; i++)
    {
        pca_9555_0_iotest();
    }

    for (int i = 0; i < 5; i++)
    {
        vTaskDelay(100);
        pca_9555_0_set_all_outputs_high();
        vTaskDelay(100);
        pca_9555_0_set_all_outputs_low();
    }
}
