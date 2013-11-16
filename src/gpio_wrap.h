#ifndef SRC_GPIO_WRAP_H_
#define SRC_GPIO_WRAP_H_

#include "node.h"
#include "gpio.h"

#define THROW_ERROR(message) \
    ThrowException(Exception::Error(String::New(message)));

#define THROW_TYPE_ERROR(message) \
    ThrowException(Exception::TypeError(String::New(message)));

class GPIOWrap: public node::ObjectWrap {
    public:
        static void Initialize(v8::Handle<v8::Object> exports,
                v8::Handle<v8::Object> module);

    private:
        explicit GPIOWrap(int id);
        ~GPIOWrap();

        static v8::Handle<v8::Value> New(const v8::Arguments &args);
        static v8::Handle<v8::Value> Value(const v8::Arguments &args);
        static v8::Handle<v8::Value> ActiveLow(const v8::Arguments &args);
        static v8::Handle<v8::Value> Direction(const v8::Arguments &args);

        static v8::Persistent<v8::Function> constructor;

        GPIO * gpio_;
};

#endif
