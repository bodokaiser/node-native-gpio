#ifndef GPIO_H
#define GPIO_H

#define GPIO_IN     0
#define GPIO_OUT    1

#define GPIO_LOW    0
#define GPIO_HIGH   1

class GPIO {
    public:
        void GPIO(int id);
        void ~GPIO();
        int  Value();
        void Value(int value);
        int  Direction();
        void Direction(int value);

    private:
        int _id;
        int _value_fd;
        int _direction_fd;

        void Exists();
        void Export();
        void Unexport();
        void OpenValueFd();
        void OpenDirectionFd();
        void CloseValueFd();
        void CloseDirectionFd();
        void SeekToTopOfValueFd();
        void SeekToTopOfDirectionFd();
};

#endif
