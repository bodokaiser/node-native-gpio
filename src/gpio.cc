#include "gpio.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
#include <stdexcept>

using std::ios;
using std::endl;
using std::string;
using std::stringstream;
using std::logic_error;
using std::runtime_error;

const char * GPIO::PATH_EXISTS    = "/sys/class/gpio/gpio%d";
const char * GPIO::PATH_EXPORT    = "/sys/class/gpio/export";
const char * GPIO::PATH_UNEXPORT  = "/sys/class/gpio/unexport";
const char * GPIO::PATH_VALUE     = "/sys/class/gpio/gpio%d/value";
const char * GPIO::PATH_DIRECTION = "/sys/class/gpio/gpio%d/direction";

GPIO::GPIO(int id) {
    id_ = id;

    Export();

    OpenValueFd();
    OpenDirectionFd();
}

GPIO::~GPIO() {
    value_.close();
    direction_.close();

    Unexport();
}

bool
GPIO::Exists() {
    stringstream path;

    path << "/sys/class/gpio/gpio";
    path << id_;

    fstream gpio;

    gpio.open(path.str());
    
    bool result = gpio.good();

    gpio.close();

    return result;
}

void
GPIO::Export() {
    if (Exists()) return;

    fstream gpio_export;
    stringstream string_stream;

    string_stream << id_;

    gpio_export.open(PATH_EXPORT, ios::out);
    gpio_export << string_stream.str();
    gpio_export.close();
}

void
GPIO::Unexport() {
    if (!Exists()) return;

    fstream gpio_unexport;
    stringstream string_stream;

    string_stream << id_;

    gpio_unexport.open(PATH_UNEXPORT, ios::out);
    gpio_unexport << string_stream.str();
    gpio_unexport.close();
}

int
GPIO::Value() {
    string value;
    
    value_.seekp(0);
    value_ >> value;

    if (value == "0") return GPIO_LOW;
    if (value == "1") return GPIO_HIGH;

    throw logic_error("Invalid GPIO value.");
}

void
GPIO::Value(int value) {
    value_.seekp(0);

    switch (value) {
        case GPIO_LOW:
            value_ << "0" << endl; 
        
            if (!value_.good())
                throw runtime_error("Error writting to value file stream.");

            break;
        case GPIO_HIGH:
            value_ << "1" << endl; 
        
            if (!value_.good())
                throw runtime_error("Error writting to value file stream.");

            break;
        default:
            throw logic_error("Error cannot set invalid GPIO value.");
    }
}

int
GPIO::Direction() {
    string direction;

    direction_.seekp(0);

    direction_ >> direction;

    if (direction == "in") return GPIO_IN;
    if (direction == "out") return GPIO_OUT;

    throw logic_error("Invalid GPIO direction.");
}

void
GPIO::Direction(int value) {
    direction_.seekp(0);

    switch (value) {
        case GPIO_IN:
            direction_ << "in" << endl;
            
            if (!direction_.good())
                throw runtime_error("Error writting to direciton file stream.");
            
            break;
        case GPIO_OUT:
            direction_ << "out" << endl;
            
            if (!direction_.good())
                throw runtime_error("Error writting to direciton file stream.");
            
            break;
        default:
            throw logic_error("Error cannot set invalid GPIO direction.");
    }
}

void
GPIO::OpenValueFd() {
    stringstream value_path;

    value_path << "/sys/class/gpio/gpio";
    value_path << id_;
    value_path << "/value";

    value_.open(value_path.str());
}

void
GPIO::OpenDirectionFd() {
    stringstream direction_path;

    direction_path << "/sys/class/gpio/gpio";
    direction_path << id_;
    direction_path << "/direction";

    direction_.open(direction_path.str());
}
