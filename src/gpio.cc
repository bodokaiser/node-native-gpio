#include "node.h"
#include "gpio.h"
#include "gpio_util.h"
#include "gpio_util.c"

using namespace v8;

GPIO::GPIO(int id) {
    _id = id;

    gpio_export(_id);
}

GPIO::~GPIO() {
    gpio_unexport(_id);
}

void
GPIO::Initialize(Handle<Object> target) {
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

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
            FunctionTemplate::New(Values)->GetFunction());
    tpl->PrototypeTemplate()
        ->Set(String::NewSymbol("direction"), 
            FunctionTemplate::New(Direction)->GetFunction());

    target->Set(String::NewSymbol("exports"),
            Persistent<Function>::New(tpl->GetFunction()));
}

Handle<Value>
GPIO::New(const Arguments &args) {
    HandleScope scope;

    if (!args[0]->IsUint32())
        return THROW_TYPE_ERROR("GPIO id must be an integer.");

    GPIO * gpio = new GPIO(args[0]->Int32Value());

    gpio->Wrap(args.This());

    return scope.Close(args.This());
}

Handle<Value>
GPIO::Values(const Arguments &args) {
    HandleScope scope;

    GPIO * gpio = ObjectWrap::Unwrap<GPIO>(args.This());

    if (args[0]->IsUndefined()) {
        int result = gpio_read_value(gpio->_id);

        if (result == -1)
            return THROW_ERROR("Error on reading GPIO value.");

        return scope.Close(Integer::New(result));
    }

    if (args[0]->Int32Value() != GPIO_LOW && args[0]->Int32Value() != GPIO_HIGH)
        return THROW_TYPE_ERROR("GPIO value must be either LOW or HIGH.");
    
    int result = gpio_write_value(gpio->_id, args[0]->Int32Value());

    if (result == -1)
        return THROW_ERROR("Error on writing GPIO value.");


    return scope.Close(args.This());
}

Handle<Value>
GPIO::Direction(const Arguments &args) {
    HandleScope scope;

    GPIO * gpio = ObjectWrap::Unwrap<GPIO>(args.This());

    if (args[0]->IsUndefined()) {
        int result = gpio_read_direction(gpio->_id);

        if (result == -1)
            return THROW_ERROR("Error on reading GPIO direction.");

        return scope.Close(Integer::New(result));
    }

    if (args[0]->Int32Value() != GPIO_IN && args[0]->Int32Value() != GPIO_OUT)
        return THROW_TYPE_ERROR("GPIO direction must be either IN or OUT.");
    
    int result = gpio_write_direction(gpio->_id, args[0]->Int32Value());

    if (result == -1)
        return THROW_ERROR("Error on writing GPIO direction.");


    return scope.Close(args.This());
}

void
Initialize(Handle<Object> exports, Handle<Object> module) {
    GPIO::Initialize(module);
}

NODE_MODULE(gpio, Initialize);
