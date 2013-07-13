#include "../src/gpio.c"
#include <unistd.h>

int 
test_gpio_exists_true() {
    int fd;
    
    if (access("/sys/class/gpio/gpio36", F_OK) == -1) {
        fd = open("/sys/class/gpio/export", O_WRONLY);
        write(fd, "36", 2);
        close(fd);
    }

    int exists = gpio_exists(36);

    if (exists == -1) {
        perror("Error on executing gpio_exists.");
        return -1;
    }

    if (exists != 1) {
        perror("gpio_exists should return 1.");
        return -1;
    }

    return 0;
}

int 
test_gpio_exists_false() {
    int fd;
    
    if (access("/sys/class/gpio/gpio38", F_OK) == 0) {
        fd = open("/sys/class/gpio/unexport", O_WRONLY);
        write(fd, "38", 2);
        close(fd);
    }

    int exists = gpio_exists(38);

    if (exists == -1) {
        perror("Error on executing gpio_exists.");
        return -1;
    }

    if (exists != 0) {
        perror("gpio_exists should return 0.");
        return -1;
    }
    
    return 0;
}

int test_gpio_export() {
    int fd;
    
    if (access("/sys/class/gpio/gpio38", F_OK) == 0) {
        fd = open("/sys/class/gpio/unexport", O_WRONLY);
        write(fd, "38", 2);
        close(fd);
    }

    gpio_export(38);

    int exists = access("/sys/class/gpio/gpio38", F_OK);

    if (exists == -1) {
        perror("Exported gpio does not exist.");
        return -1;
    }
    
    return 0;
}

int test_gpio_unexport() {
    int fd;
    
    if (access("/sys/class/gpio/gpio42", F_OK) == -1) {
        fd = open("/sys/class/gpio/export", O_WRONLY);
        write(fd, "42", 2);
        close(fd);
    }

    gpio_unexport(42);

    int exists = access("/sys/class/gpio/gpio42", F_OK);

    if (exists == 0) {
        perror("Unexported gpio does exist.");
        return -1;
    }
    
    return 0;
}

int
test_gpio_read_direction_in() {
    gpio_export(36);

    int fd = open("/sys/class/gpio/gpio36/direction", O_WRONLY);
    write(fd, "in\n", 3);
    close(fd);
    
    int result = gpio_read_direction(36);

    if (result == -1) {
        perror("Error reading gpio direction.");
        return -1;
    }

    if (result != GPIO_IN) {
        perror("GPIO direction should equal GPIO_IN.");
        return -1;
    }

    return 0;
}

int
test_gpio_read_direction_out() {
    gpio_export(38);

    int fd = open("/sys/class/gpio/gpio38/direction", O_WRONLY);
    write(fd, "out\n", 4);
    close(fd);
    
    int result = gpio_read_direction(38);

    if (result == -1) {
        perror("Error reading gpio direction.");
        return -1;
    }

    if (result != GPIO_OUT) {
        perror("GPIO direction should equal GPIO_OUT.");
        return -1;
    }

    return 0;
}

int
test_gpio_write_direction_in() {
    gpio_export(40);
    gpio_write_direction(40, GPIO_IN);

    char data[3];

    data[2] = 0;

    int fd = open("/sys/class/gpio/gpio40/direction", O_RDONLY);
    read(fd, data, 2);
    close(fd);

    if (strncmp(data, "in", 2) != 0) {
        perror("Direction should be in.");
        return -1;
    }

    return 0;
}

int
test_gpio_write_direction_out() {
    gpio_export(42);
    gpio_write_direction(42, GPIO_OUT);

    char data[4];

    data[3] = 0;

    int fd = open("/sys/class/gpio/gpio42/direction", O_RDONLY);
    read(fd, data, 3);
    close(fd);

    if (strncmp(data, "out", 3) != 0) {
        perror("Direction should be out.");
        return -1;
    }

    return 0;
}

int
test_gpio_read_value_low() {
    gpio_export(36);
    gpio_write_direction(36, GPIO_OUT);

    int fd = open("/sys/class/gpio/gpio36/value", O_WRONLY);
    write(fd, "0\n", 2);
    close(fd);
    
    int result = gpio_read_value(36);

    if (result == -1) {
        perror("Error reading gpio value.");
        return -1;
    }

    if (result != GPIO_LOW) {
        perror("GPIO value should equal GPIO_LOW.");
        return -1;
    }

    return 0;
}

int
test_gpio_read_value_high() {
    gpio_export(38);
    gpio_write_direction(38, GPIO_OUT);

    int fd = open("/sys/class/gpio/gpio38/value", O_WRONLY);
    write(fd, "1\n", 2);
    close(fd);
    
    int result = gpio_read_value(38);

    if (result == -1) {
        perror("Error reading gpio value.");
        return -1;
    }

    if (result != GPIO_HIGH) {
        perror("GPIO value should equal GPIO_HIGH.");
        return -1;
    }

    return 0;
}

int
test_gpio_write_value_low() {
    gpio_export(36);
    gpio_write_value(36, GPIO_LOW);

    char data[2];

    data[1] = 0;

    int fd = open("/sys/class/gpio/gpio36/value", O_RDONLY);
    read(fd, data, 1);
    close(fd);

    if (strncmp(data, "0", 1) != 0) {
        perror("Value should be 0.");
        return -1;
    }

    return 0;
}

int
test_gpio_write_value_high() {
    gpio_export(38);
    gpio_write_value(38, GPIO_HIGH);

    char data[2];

    data[1] = 0;

    int fd = open("/sys/class/gpio/gpio38/value", O_RDONLY);
    read(fd, data, 1);
    close(fd);

    if (strncmp(data, "1", 1) != 0) {
        perror("Value should be 1.");
        return -1;
    }

    return 0;
}

int 
main(int argc, const char ** argv) {
    if (test_gpio_exists_true() != 0) {
        perror("Test: test_gpio_exists_true failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_exists_true success.\n");
    }
 
    if (test_gpio_exists_false() != 0) {
        perror("Test: test_gpio_exists_false failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_exists_false success.\n");
    }

    if (test_gpio_export() != 0) {
        perror("Test: test_gpio_export failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_export success.\n");
    }

    if (test_gpio_unexport() != 0) {
        perror("Test: test_gpio_unexport failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_unexport success.\n");
    }

    if (test_gpio_read_direction_in() != 0) {
        perror("Test: test_gpio_read_direction_in failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_read_direction_in success.\n");
    }

    if (test_gpio_read_direction_out() != 0) {
        perror("Test: test_gpio_read_direction_out failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_read_direction_out success.\n");
    }

    if (test_gpio_write_direction_in() != 0) {
        perror("Test: test_gpio_write_direction_in failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_write_direction_in success.\n");
    }

    if (test_gpio_write_direction_out() != 0) {
        perror("Test: test_gpio_write_direction_out failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_write_direction_out success.\n");
    }

    if (test_gpio_read_value_low() != 0) {
        perror("Test: test_gpio_read_value_low failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_read_value_low success.\n");
    }

    if (test_gpio_read_value_high() != 0) {
        perror("Test: test_gpio_read_value_high failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_read_value_high success.\n");
    }

    if (test_gpio_write_value_low() != 0) {
        perror("Test: test_gpio_write_value_low failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_write_value_low success.\n");
    }

    if (test_gpio_write_value_high() != 0) {
        perror("Test: test_gpio_write_value_high failed.");
        return EXIT_FAILURE;
    } else {
        printf("Test: test_gpio_write_value_high success.\n");
    }

    return EXIT_SUCCESS;
}
