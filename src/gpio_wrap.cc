#include "node.h"
#include "gpio.cc"
#include "gpio_wrap.h"

#include <exception>

using std::exception;

using v8::Exception;
using v8::HandleScope;
using v8::Local;
using v8::Handle;
using v8::Persistent;
using v8::Value;
using v8::String;
using v8::Integer;
using v8::Object;
using v8::Function;
using v8::FunctionTemplate;
using v8::Arguments;

GPIOWrap::GPIOWrap(int id) {
    gpio_ = new GPIO(id);
}

GPIOWrap::~GPIOWrap() {
    delete gpio_;
}

Persistent<Function>
GPIOWrap::constructor;

Handle<Value>
GPIOWrap::New(const Arguments &args) {
    HandleScope scope;

    if (!args[0]->IsUint32())
        return THROW_TYPE_ERROR("GPIO id must be an integer.");

    if (args.IsConstructCall()) {
        GPIOWrap * gpio_wrap;

        try {
            gpio_wrap = new GPIOWrap(args[0]->Int32Value());
        } catch(const exception &error) {
            return THROW_ERROR(error.what());
        }

        gpio_wrap->Wrap(args.This());

        return scope.Close(args.This());
    } else {
        const int argc = 1;

        Local<v8::Value> argv[argc] = { args[0] };

        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Value>
GPIOWrap::Value(const Arguments &args) {
    HandleScope scope;

    GPIOWrap * gpio_wrap = ObjectWrap::Unwrap<GPIOWrap>(args.This());

    int value;

    switch (args.Length()) {
        case 0:
            try {
                value = gpio_wrap->gpio_->GetValue();
            } catch(const exception &error) {
                return THROW_ERROR(error.what());
            }

            return scope.Close(Integer::New(value));
        case 1:
            value = args[0]->Int32Value();

            if (value != GPIO_LOW && value != GPIO_HIGH)
                return THROW_TYPE_ERROR("Value must be either LOW or HIGH.");

            try {
                gpio_wrap->gpio_->SetValue(value);
            } catch(const exception &error) {
                return THROW_ERROR(error.what());
            }

            return scope.Close(args.This());
    }

    return THROW_TYPE_ERROR("Invalid arguments length.");
}

Handle<Value>
GPIOWrap::ActiveLow(const Arguments &args) {
    HandleScope scope;

    GPIOWrap * gpio_wrap = ObjectWrap::Unwrap<GPIOWrap>(args.This());

    int value;

    switch (args.Length()) {
        case 0:
            try {
                value = gpio_wrap->gpio_->GetActiveLow();
            } catch(const exception &error) {
                return THROW_ERROR(error.what());
            }

            return scope.Close(Integer::New(value));
        case 1:
            value = args[0]->Int32Value();

            if (value != GPIO_LOW && value != GPIO_HIGH)
                return THROW_TYPE_ERROR("Value must be either LOW or HIGH.");

            try {
                gpio_wrap->gpio_->SetActiveLow(value);
            } catch(const exception &error) {
                return THROW_ERROR(error.what());
            }

            return scope.Close(args.This());
    }

    return THROW_TYPE_ERROR("Invalid arguments length.");
}

Handle<Value>
GPIOWrap::Direction(const Arguments &args) {
    HandleScope scope;

    GPIOWrap * gpio_wrap = ObjectWrap::Unwrap<GPIOWrap>(args.This());

    int value;

    switch (args.Length()) {
        case 0:
            try {
                value = gpio_wrap->gpio_->GetDirection();
            } catch(const exception &error) {
                return THROW_ERROR(error.what());
            }

            return scope.Close(Integer::New(value));
        case 1:
            value = args[0]->Int32Value();

            if (value != GPIO_IN && value != GPIO_OUT)
                return THROW_TYPE_ERROR("Value must be either IN or OUT.");

            try {
                gpio_wrap->gpio_->SetDirection(value);
            } catch(const exception &error) {
                return THROW_ERROR(error.what());
            }

            return scope.Close(args.This());
    }

    return THROW_TYPE_ERROR("Invalid arguments length.");
}

void
GPIOWrap::Initialize(Handle<Object> exports, Handle<Object> module) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(GPIOWrap::New);

    tpl->SetClassName(String::NewSymbol("GPIO"));

    tpl->InstanceTemplate()
        ->SetInternalFieldCount(1);

    tpl->Set(String::NewSymbol("IN"),
            Integer::New(GPIO_IN));
    tpl->Set(String::NewSymbol("OUT"),
            Integer::New(GPIO_OUT));
    tpl->Set(String::NewSymbol("LOW"),
            Integer::New(GPIO_LOW));
    tpl->Set(String::NewSymbol("HIGH"),
            Integer::New(GPIO_HIGH));

    tpl->PrototypeTemplate()
        ->Set(String::NewSymbol("value"),
            FunctionTemplate::New(GPIOWrap::Value)->GetFunction());
    tpl->PrototypeTemplate()
        ->Set(String::NewSymbol("activeLow"),
            FunctionTemplate::New(GPIOWrap::ActiveLow)->GetFunction());
    tpl->PrototypeTemplate()
        ->Set(String::NewSymbol("direction"),
            FunctionTemplate::New(GPIOWrap::Direction)->GetFunction());

    module->Set(String::NewSymbol("exports"),
            Persistent<Function>::New(tpl->GetFunction()));

    constructor = Persistent<Function>::New(tpl->GetFunction());
}

NODE_MODULE(gpio, GPIOWrap::Initialize);
