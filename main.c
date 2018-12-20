// This is doing a 1000 loops with a 1 sec sleep between HIGH and LOW of the
// GPIO pin labelled "CTS" on my USEN dongle "ALL IN ONE I2C/SPI/UART/MEM/EPP".

#include "ch341a.h"
#include <unistd.h>

int testblink() {
    int32_t ret;
    uint8_t gpio_dir_mask = 0b01111111;
    uint8_t gpio_data = 0;

    ret = ch341a_gpio_configure(&gpio_dir_mask);
    if (ret < 0) return -1;

    int i = 0;
    for (i = 0 ; i < 10000 ; i++) {
        gpio_data ^= 1;
        usleep(1000000);
        ret = ch341a_gpio_instruct(&gpio_dir_mask, &gpio_data);
        if (ret < 0) return -1;
        printf("data: %x\n", gpio_data);
    }
    return ret;
}

int main() {
    int ret;

    ret = ch341a_configure(CH341A_USB_VENDOR, CH341A_USB_PRODUCT);
    if (ret < 0) return -1;

    ret = testblink();

    printf("\nreturn: %d\n", ret);
    return ch341a_release();
}
