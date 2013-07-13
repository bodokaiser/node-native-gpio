#ifndef GPIO_H
#define GPIO_H

#define THROW_ERROR(message) \
    ThrowException(Exception::Error(String::New(message)));

#define THROW_TYPE_ERROR(message) \
    ThrowException(Exception::TypeError(String::New(message)));

using namespace v8;

using node::ObjectWrap;

class GPIO: public ObjectWrap {
    public:
        static void Initialize(Handle<Object> target);

    private:
        GPIO(int id);
        ~GPIO();

        int _id;

        static Handle<Value> New(const Arguments &args);
        static Handle<Value> Values(const Arguments &args);
        static Handle<Value> Direction(const Arguments &args);
};

#endif
