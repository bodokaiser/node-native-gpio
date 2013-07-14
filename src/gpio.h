#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include <string>
#include <fstream>
#include <iostream>

using std::string;
using std::fstream;

enum GPIODirection {
    GPIO_IN  = 0,
    GPIO_OUT = 1
};

enum GPIOValue {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
};

class GPIO {
    public:
        explicit GPIO(int id);
        ~GPIO();

        int  Value();
        void Value(int value);
        int  Direction();
        void Direction(int value);

    private:
        int id_;

        fstream value_;
        fstream direction_;

        bool Exists();
        void Export();
        void Unexport();
        void OpenValueFd();
        void OpenDirectionFd();
        void CloseValueFd();
        void CloseDirectionFd();
        void SeekToTopOfValueFd();
        void SeekToTopOfDirectionFd();

        static const char * PATH_EXISTS;
        static const char * PATH_EXPORT;
        static const char * PATH_UNEXPORT;
        static const char * PATH_VALUE;
        static const char * PATH_DIRECTION;
};

#endif
