#include "../src/gpio.c"
#include <unistd.h>

int test_gpio_exists() {
    int exists = access("/sys/class/gpio/gpio34", F_OK);

    printf("%d", exists);

    return 0;
}

int main(int argc, const char ** argv) {
    if (test_gpio_exists != 0) {
        perror("test_gpio_exists failed.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
