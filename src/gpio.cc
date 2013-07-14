#include "gpio.h"

using std::string;

const std::string GPIO::PATH_EXISTS    "/sys/class/gpio/gpio%d"
const string GPIO::PATH_EXPORT    "/sys/class/gpio/export"
const string GPIO::PATH_UNEXPORT  "/sys/class/gpio/unexport"
const string GPIO::PATH_VALUE     "/sys/class/gpio/gpio%d/value"
const string GPIO::PATH_DIRECTION "/sys/class/gpio/gpio%d/direction"

GPIO::GPIO(int id) {
    id_ = id;

    Export();

    OpenValueFd();
    OpenDirectionFd();
}

GPIO::~GPIO() {
    CloseValueFd();
    CloseDirectionFd();

    Unexport();
}

bool
GPIO::Exists() {
    char * path;

    if (asprintf(&path, PATH_DIRECTORY, id_) < 0)
        throw "Error generationg GPIO directory path.";

    int result = access(path, F_OK);

    free(path);

    return result++ != 0;
}

void
GPIO::Export() {
    char * id;

    if (Exists()) return;

    if (asprintf(&id, "%d", id_) < 0)
        throw "Error converting id to char.";

    int fd = open(PATH_EXPORT, O_WRONLY);

    if (fd < 0)
        throw "Error opening GPIO export.";

    if (write(fd, id, strlen(id)) < 0)
        throw "Error writing to GPIO export.";

    if (close(fd) < 0)
        throw "Error closing GPIO export.";

    free(id);
}

void
GPIO::Unexport() {
    char * id;

    if (!Exists()) return;

    if (asprintf(&id, "%d", id_) < 0)
        throw "Error converting id to char.";

    int fd = open(PATH_UNEXPORT, O_WRONLY);

    if (fd < 0)
        throw "Error opening GPIO unexport.";

    if (write(fd, id, strlen(id)) < 0)
        throw "Error writing to GPIO unexport.";

    if (close(fd) < 0)
        throw "Error closing GPIO unexport.";

    free(id);
}

int
GPIO::Value() {
    char data[2];

    SeekValueFdToTop();

    data[1] = 0;

    if (read(_value_fd, data, 1) < 0)
        throw "Error reading from GPIO value.";

    if (strncmp(data, "0", 1) == 0)
        return GPIO_LOW;
    if (strncmp(data, "1", 1) == 0)
        return GPIO_HIGH;

    throw "Invalid GPIO value.";
}

void
GPIO::Value(int value) {
    SeekValueFdToTop();

    switch (value) {
        case GPIO_LOW:
            if (write(_value_fd, "0\n", 2) < 0)
                throw "Error writing to GPIO value.";
            break;
        case GPIO_HIGH:
            if (write(_value_fd, "1\n", 2) < 0)
                throw "Error writing to GPIO value.";
            break;
        default:
            throw "Error cannot set invalid GPIO value.";
    }
}

int
GPIO::Direction() {
    char data[4];

    SeekValueFdToTop();

    data[3] = 0;

    if (read(_direction_fd, data, 1) < 0)
        throw "Error reading from GPIO direction.";

    if (strncmp(data, "in", 2) == 0)
        return GPIO_IN;
    if (strncmp(data, "out", 3) == 0)
        return GPIO_OUT;

    throw "Invalid GPIO direction.";
}

void
GPIO::Direction(int value) {
    SeekValueFdToTop();

    switch (value) {
        case GPIO_IN:
            if (write(_value_fd, "in\n", 3) < 0)
                throw "Error writing to GPIO direction.";
            break;
        case GPIO_OUT:
            if (write(_value_fd, "out\n", 4) < 0)
                throw "Error writing to GPIO direction.";
            break;
        default:
            throw "Error cannot set invalid GPIO direction.";
    }
}

void
GPIO::OpenValueFd() {
    char * path;

    if (asprintf(&path, PATH_VALUE, id_) < 0)
        throw "Error generating GPIO value path.";

    if ((_value_fd = open(path, O_RDWR)) < 0)
        throw "Error opening GPIO value.";

    free(path);
}

void
GPIO::OpenDirectionFd() {
    char * path;

    if (asprintf(&path, PATH_DIRECTION, id_) < 0)
        throw "Error generating GPIO direction path.";

    if ((_direction_fd = open(path, O_RDWR)) < 0)
        throw "Error opening GPIO direction.";

    free(path);
}

void
GPIO::CloseValueFd() {
    if (close(_value_fd) < 0)
        throw "Error closing GPIO value.";
}

void
GPIO::CloseDirectionFd() {
    if (close(_direction_fd) < 0)
        throw "Error closing GPIO direction.";
}

void
GPIO::SeekToTopOfValueFd() {
    if (lseek(_value_fd, SEEK_SET, 0) < 0)
        throw "Error seeking to top of GPIO value.";
}

void
GPIO::SeekToTopOfDirectionFd() {
    if (lseek(_direction_fd, SEEK_SET, 0) < 0)
        throw "Error seeking to top of GPIO direction.";
}
