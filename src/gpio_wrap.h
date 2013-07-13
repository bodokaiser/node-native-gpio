#ifndef GPIO_WRAP_H
#define GPIO_WRAP_H

#define THROW_ERROR(message) \
    ThrowException(Exception::Error(String::New(message)));

#define THROW_TYPE_ERROR(message) \
    ThrowException(Exception::TypeError(String::New(message)));

using namespace v8;

using node::ObjectWrap;

class GPIOWrap: public ObjectWrap {
    private:
        GPIOWrap();
        ~GPIOWrap();

        static Handle<Value> New(const Arguments &args);
        static Handle<Value> Values(const Arguments &args);
        static Handle<Value> Direction(const Arguments &args);
};

#endif
