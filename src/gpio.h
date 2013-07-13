#ifndef GPIO_H
#define GPIO_H

#define GPIO_IN                 "in\n"
#define GPIO_OUT                "out\n"

#define GPIO_LOW                "0\n"
#define GPIO_HIGH               "1\n"

#define GPIO_PATH_EXPORT        "/sys/class/gpio/export"
#define GPIO_PATH_UNEXPORT      "/sys/class/gpio/unexport"
#define GPIO_PATH_DIRECTORY     "/sys/class/gpio/gpio%d"
#define GPIO_PATH_DIRECTION     "/sys/class/gpio/gpio%d/direction"
#define GPIO_PATH_VALUE         "/sys/class/gpio/gpio%d/value"

int
gpio_exists(int pin);

int
gpio_export(int pin);

int
gpio_unexport(int pin);

int
gpio_direction(int pin);

int
gpio_value(int pin);

#endif
