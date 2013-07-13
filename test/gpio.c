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
        perror("exported gpio does not exist.");
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

    gpio_export(42);

    int exists = access("/sys/class/gpio/gpio42", F_OK);

    if (exists == 0) {
        perror("unexported gpio does exist.");
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

    return EXIT_SUCCESS;
}
