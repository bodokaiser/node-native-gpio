#include <node.h>

#include "../src/gpio.h"
#include "../src/gpio_wrap.h"

using v8::Persistent;
using v8::Handle;
using v8::Local;
using v8::Value;
using v8::String;
using v8::Integer;
using v8::Object;
using v8::Function;
using v8::FunctionTemplate;
using v8::Arguments;
using v8::HandleScope;
using v8::Exception;

GPIOWrap::GPIOWrap(int id) {
    gpio_ = new GPIO(id);
}

GPIOWrap::~GPIOWrap() {}

Handle<Value>
GPIOWrap::New(const Arguments &args) {
    HandleScope scope;

    if (!args[0]->IsUint32())
        return THROW_TYPE_ERROR("GPIO id must be an integer.");

    GPIOWrap * gpio_wrap = new GPIOWrap(args[0]->Int32Value());

    gpio_wrap->Wrap(args.This());

    return scope.Close(args.This());
}

Handle<Value>
GPIOWrap::Value(const Arguments &args) {
    HandleScope scope;

    GPIO * gpio = ObjectWrap::Unwrap<GPIOWrap>(args.This())->gpio_;

    int value;

    switch (args.Length()) {
        case 0:
            value = gpio->Value();

            return scope.Close(Integer::New(value));
        case 1:
            value = args[0]->Int32Value();

            if (value != GPIO_LOW && value != GPIO_HIGH)
                return THROW_TYPE_ERROR("Value must be either LOW or HIGH.");

            gpio->Value(value);

            return scope.Close(args.This());
    }

    return THROW_TYPE_ERROR("Invalid arguments length.");
}

Handle<Value>
GPIOWrap::Direction(const Arguments &args) {
    HandleScope scope;

    GPIO * gpio = ObjectWrap::Unwrap<GPIOWrap>(args.This())->gpio_;

    int value;

    switch (args.Length()) {
        case 0:
            value = gpio->Direction();

            return scope.Close(Integer::New(value));
        case 1:
            value = args[0]->Int32Value();

            if (value != GPIO_IN && value != GPIO_OUT)
                return THROW_TYPE_ERROR("Value must be either IN or OUT.");

            gpio->Direction(value);

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
        ->Set(String::NewSymbol("direction"),
            FunctionTemplate::New(GPIOWrap::Direction)->GetFunction());

    module->Set(String::NewSymbol("exports"),
            Persistent<Function>::New(tpl->GetFunction()));
}

NODE_MODULE(gpio, GPIOWrap::Initialize);
