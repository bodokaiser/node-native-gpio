#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include <string>

enum GPIODirection {
    GPIO_IN  = 0,
    GPIO_OUT = 1
};

enum GPIOValue {
    GPIO_LOW  = 0,
    GPIO_HIGH = 1
};

using std::string;

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
        int value_fd_;
        int direction_fd_;

        bool Exists();
        void Export();
        void Unexport();
        void OpenValueFd();
        void OpenDirectionFd();
        void CloseValueFd();
        void CloseDirectionFd();
        void SeekToTopOfValueFd();
        void SeekToTopOfDirectionFd();

        static const string PATH_EXISTS;
        static const string PATH_EXPORT;
        static const string PATH_UNEXPORT;
        static const string PATH_VALUE;
        static const string PATH_DIRECTION;
};

#endif
