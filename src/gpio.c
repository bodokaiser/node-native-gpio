#include "gpio.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_PATH_EXPORT        "/sys/class/gpio/export"
#define GPIO_PATH_UNEXPORT      "/sys/class/gpio/unexport"
#define GPIO_PATH_DIRECTORY     "/sys/class/gpio/gpio%d"
#define GPIO_PATH_DIRECTION     "/sys/class/gpio/gpio%d/direction"
#define GPIO_PATH_VALUE         "/sys/class/gpio/gpio%d/value"

int
gpio_exists(int id) {
    char * path;

    if (asprintf(&path, GPIO_PATH_DIRECTORY, id) < 0) {
        perror("Error generating GPIO directory path.");
        return -1;
    }

    int result = access(path, F_OK);

    free(path);

    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int
gpio_export(int id) {
    char * stringified_id;

    if (gpio_exists(id)) return 0;

    if (asprintf(&stringified_id, "%d", id) < 0) {
        perror("Error transforming GPIO id to string.");
        return -1;
    }

    int fd = open(GPIO_PATH_EXPORT, O_WRONLY);

    if (fd < 0) {
        perror("Error opening GPIO export.");
        return -1;
    }

    if (write(fd, stringified_id, strlen(stringified_id)) < 0) {
        perror("Error writing to GPIO export.");
        return -1;
    }

    if (close(fd) < 0) {
        perror("Error closing GPIO export.");
        return -1;
    }

    free(stringified_id);

    return 0;
}

int
gpio_unexport(int id) {
    char * stringified_id;

    if (!gpio_exists(id)) return 0;

    if (asprintf(&stringified_id, "%d", id) < 0) {
        perror("Error transforming GPIO id to string.");
        return -1;
    }

    int fd = open(GPIO_PATH_UNEXPORT, O_WRONLY);

    if (fd < 0) {
        perror("Error opening GPIO unexport.");
        return -1;
    }

    if (write(fd, stringified_id, strlen(stringified_id)) < 0) {
        perror("Error writing to GPIO unexport.");
        return -1;
    }

    if (close(fd) < 0) {
        perror("Error closing GPIO unexport.");
        return -1;
    }

    free(stringified_id);

    return 0;
}

int
gpio_read_direction(int id) {
    char data[4];
    char * path;

    if (gpio_exists(id) != 1) {
        perror("GPIO does not exists.");
        return -1;
    }

    data[3] = 0;

    if (asprintf(&path, GPIO_PATH_DIRECTION, id) < 0) {
        perror("Error generating GPIO direction path.");
        return -1;
    }

    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        perror("Error opening GPIO direction.");
        return -1;
    }

    if (read(fd, &data, 3) < 0) {
        perror("Error reading GPIO direction.");
        return -1;
    }

    if (close(fd) < 0) {
        perror("Error closing GPIO direction.");
        return -1;
    }

    free(path);

    if (strncmp(data, "in", 2) == 0) {
        return GPIO_IN;
    } else if (strncmp(data, "out", 3) == 0) {
        return GPIO_OUT;
    } else {
        perror("Error comparing GPIO direction with values.");
        return -1;
    }
}

int
gpio_write_direction(int id, int value) {
    char * path;

    if (gpio_exists(id) != 1) {
        perror("GPIO does not exists.");
        return -1;
    }

    if (asprintf(&path, GPIO_PATH_DIRECTION, id) < 0) {
        perror("Error generating GPIO direction path.");
        return -1;
    }

    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        perror("Error opening GPIO direction.");
        return -1;
    }

    switch (value) {
        case GPIO_IN:
            if (write(fd, "in\n", 3) < 0) {
                perror("Error writing to GPIO direction.");
                return -1;
            }
            break;
        case GPIO_OUT:
            if (write(fd, "out\n", 4) < 0) {
                perror("Error writing to GPIO direction.");
                return -1;
            }
            break;
        default:
            perror("Invalid GPIO direction code.");
            return -1;
    }

    if (close(fd) < 0) {
        perror("Error closing GPIO direction.");
        return -1;
    }

    free(path);

    return 0;
}

int
gpio_read_value(int id) {
    char data[2];
    char * path;

    if (gpio_exists(id) != 1) {
        perror("GPIO does not exists.");
        return -1;
    }

    data[1] = 0;

    if (asprintf(&path, GPIO_PATH_VALUE, id) < 0) {
        perror("Error generating GPIO value path.");
        return -1;
    }

    int fd = open(path, O_RDONLY);

    if (fd < 0) {
        perror("Error opening GPIO value.");
        return -1;
    }

    if (read(fd, &data, 1) < 0) {
        perror("Error reading GPIO value.");
        return -1;
    }

    if (close(fd) < 0) {
        perror("Error closing GPIO value.");
        return -1;
    }

    free(path);

    if (strncmp(data, "0", 1) == 0) {
        return GPIO_LOW;
    } else if (strncmp(data, "0", 1) == 0) {
        return GPIO_HIGH;
    } else {
        perror("Error comparing GPIO value with values.");
        return -1;
    }
}

int
gpio_write_value(int id, int value) {
    char * path;

    if (gpio_exists(id) != 1) {
        perror("GPIO does not exists.");
        return -1;
    }

    if (asprintf(&path, GPIO_PATH_VALUE, id) < 0) {
        perror("Error generating GPIO value path.");
        return -1;
    }

    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        perror("Error opening GPIO value.");
        return -1;
    }

    switch (value) {
        case GPIO_LOW:
            if (write(fd, "0\n", 2) < 0) {
                perror("Error writing to GPIO value.");
                return -1;
            }
            break;
        case GPIO_HIGH:
            if (write(fd, "1\n", 2) < 0) {
                perror("Error writing to GPIO value.");
                return -1;
            }
            break;
        default:
            perror("Invalid GPIO value code.");
            return -1;
    }

    if (close(fd) < 0) {
        perror("Error closing GPIO value.");
        return -1;
    }

    free(path);

    return 0;
}
