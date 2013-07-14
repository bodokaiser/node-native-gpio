#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#define GPIO_IN     0
#define GPIO_OUT    1

#define GPIO_LOW    0
#define GPIO_HIGH   1

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
};

#endif
