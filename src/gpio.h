#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include <string>
#include <fstream>
#include <iostream>

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

        int  GetValue();
        void SetValue(int value);
        int  GetActiveLow();
        void SetActiveLow(int value);
        int  GetDirection();
        void SetDirection(int value);

    private:
        int id_;

        std::fstream value_stream_;
        std::fstream active_low_stream_;
        std::fstream direction_stream_;

        bool Exists();
        void Export();
        void Unexport();

        static const std::string PATH_EXPORT;
        static const std::string PATH_UNEXPORT;
        static const std::string PREFIX;
        static const std::string POSTFIX_VALUE;
        static const std::string POSTFIX_ACTIVE_LOW;
        static const std::string POSTFIX_DIRECTION;
};

#endif
