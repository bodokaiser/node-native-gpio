#ifndef GPIO_H
#define GPIO_H

#define GPIO_IN     0
#define GPIO_OUT    1

#define GPIO_LOW    0
#define GPIO_HIGH   1

int
gpio_exists(int id);

int
gpio_export(int id);

int
gpio_unexport(int id);

int
gpio_read_direction(int id);

int
gpio_write_direction(int id, int value);

int
gpio_read_value(int id);

int
gpio_write_value(int id, int value);

#endif
