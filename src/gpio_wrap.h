#ifndef SRC_GPIO_WRAP_H_
#define SRC_GPIO_WRAP_H_

#include "../src/gpio.h"

#define THROW_ERROR(message) \
    ThrowException(Exception::Error(String::New(message)));

#define THROW_TYPE_ERROR(message) \
    ThrowException(Exception::TypeError(String::New(message)));

using node::ObjectWrap;

class GPIOWrap: public ObjectWrap {
    public:
        static void Initialize(v8::Handle<v8::Object> exports,
                v8::Handle<v8::Object> module);

    private:
        explicit GPIOWrap(int id);
        ~GPIOWrap();

        static v8::Handle<v8::Value> New(const v8::Arguments &args);
        static v8::Handle<v8::Value> Value(const v8::Arguments &args);
        static v8::Handle<v8::Value> Direction(const v8::Arguments &args);

        GPIO * _gpio;
};

#endif
