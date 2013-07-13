#ifndef GPIO_H
#define GPIO_H

#define GPIO_IN     "in\n"
#define GPIO_OUT    "out\n"

#define GPIO_LOW    "0\n"
#define GPIO_HIGH   "1\n"

int
gpio_exists(int id);

int
gpio_export(int id);

int
gpio_unexport(int id);

int
gpio_direction(int id);

int
gpio_value(int id);

#endif
