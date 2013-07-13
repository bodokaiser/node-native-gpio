# node-native-gpio

**node-native-gpio** is a sysfs **G**eneral **P**urpose **I**nput **O**utput 
wrapper for node.js. It gives you the ability to control GPIO devices in a 
simple object orientated manner.

## Installation

Install **node-native-gpio** with [npm(1)](http://npmjs.org):

    $ npm install node-native-gpio

## Preview

    var gpio = require('native-gpio');

    var gpio22 = new gpio.GPIO(22);

    gpio22.direction(gpio.OUT)
          .value(gpio.HIGH)
          .value(gpio.LOW)
          .value(gpio.HIGH);

## Documentation

### Constants

To ensure safe execution **node-native-gpio** relays on some constants.

#### IN

Direction constant used to determinate that our GPIO device listens for 
incoming signals. While a device is set to `IN` we can only read and not write 
to it.

#### OUT

Direction constant used to determinate that our GPIO device writes outgoing
signals. While a device is set to `OUT` we can read and set the current value.

#### LOW

Value constant for off state of a GPIO device.

#### HIGH

Value constant for on state of a GPIO device.

### Class: GPIO 

#### new GPIO(pin)

#### gpio.value([value])

#### gpio.direction([value])

## License

Copyright © 2013 Bodo Kaiser <i@bodokaiser.io>

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
