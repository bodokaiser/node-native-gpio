#include "gpio.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_PATH_EXPORT    "/sys/class/gpio/export"
#define GPIO_PATH_UNEXPORT  "/sys/class/gpio/unexport"
#define GPIO_PATH_DIRECTORY "/sys/class/gpio/gpio%d"
#define GPIO_PATH_DIRECTION "/sys/class/gpio/gpio%d/direction"
#define GPIO_PATH_VALUE     "/sys/class/gpio/gpio%d/value"

int
gpio_exists(int id) {
    char * path;

    if (asprintf(&path, GPIO_PATH_DIRECTORY) != 0) {
        perror("Error generating GPIO directory path.");
        return -1;
    }

    int result = access(path, F_OK) == 0;

    free(path);

    return result;
}

int
gpio_export(int id) {
    char * stringified_id;

    if (gpio_exists(id)) return 0;

    if (asprintf(&stringified_id, "%d") != 0) {
        perror("Error transforming GPIO id to string.");
        return -1;
    }

    int fd = open(GPIO_PATH_EXPORT, O_WRONLY);

    if (fd < 0) {
        perror("Error opening GPIO export.");
        return -1;
    }

    if (write(fd, stringified_id, strlen(stringified_id)) != 0) {
        perror("Error writing to GPIO export.");
        return -1;
    }

    if (close(fd) != 0) {
        perror("Error closing GPIO export.");
        return -1;
    }

    if (free(stringified_id) != 0) {
        perror("Error freeing stringified id.");
        return -1;
    }

    return 0;
}

int
gpio_unexport(int id) {
    char * stringified_id;

    if (!gpio_exists(id)) return 0;

    if (asprintf(&stringified_id, "%d") != 0) {
        perror("Error transforming GPIO id to string.");
        return -1;
    }

    int fd = open(GPIO_PATH_UNEXPORT, O_WRONLY);

    if (fd < 0) {
        perror("Error opening GPIO unexport.");
        return -1;
    }

    if (write(fd, stringified_id, strlen(stringified_id)) != 0) {
        perror("Error writing to GPIO unexport.");
        return -1;
    }

    if (close(fd) != 0) {
        perror("Error closing GPIO unexport.");
        return -1;
    }

    if (free(stringified_id) != 0) {
        perror("Error freeing stringified id.");
        return -1;
    }

    return 0;
}

int
gpio_direction(int id) {

}

int
gpio_value(int id) {

}
