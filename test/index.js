var fs   = require('fs');
var chai = require('chai');
var GPIO = require('../lib');

describe('GPIO', function() {

    describe('new GPIO(id)', function() {

        it('should export a GPIO device', function() {
            var gpio = new GPIO(36);

            var exists = fs.existsSync('/sys/class/gpio/gpio36');

            chai.expect(exists)
                .to.equal.true;
        });

    });

    describe('gpio.value()', function() {


        it('should return "LOW" for value', function() {
            var gpio = new GPIO(42).direction(GPIO.OUT);

            fs.writeFileSync('/sys/class/gpio/gpio42/value', 
                new Buffer('0\n'));

            chai.expect(gpio.value())
                .to.equal(GPIO.LOW);
        });

        it('should return "OUT" for direction', function() {
            var gpio = new GPIO(42).direction(GPIO.OUT);

            fs.writeFileSync('/sys/class/gpio/gpio42/value', 
                new Buffer('1\n'));

            chai.expect(gpio.value())
                .to.equal(GPIO.HIGH);
        });

    });

    describe('gpio.value(value)', function() {

        it('should set the value to LOW', function() {
            var gpio = new GPIO(42)
                        .direction(GPIO.OUT)
                        .value(GPIO.LOW);

            var value = fs.readFileSync('/sys/class/gpio/gpio42/value');
        
            chai.expect(value.toString())
                .to.equal('0\n');
        });

        it('should set the value to HIGH', function() {
            var gpio = new GPIO(42)
                        .direction(GPIO.OUT)
                        .value(GPIO.HIGH);

            var value = fs.readFileSync('/sys/class/gpio/gpio42/value');
        
            chai.expect(value.toString())
                .to.equal('1\n');
        });

    });

    describe('gpio.direction()', function() {

        it('should return "IN" for direction', function() {
            var gpio = new GPIO(42);

            fs.writeFileSync('/sys/class/gpio/gpio42/direction', 
                new Buffer('in\n'));

            chai.expect(gpio.direction())
                .to.equal(GPIO.IN);
        });

        it('should return "OUT" for direction', function() {
            var gpio = new GPIO(42);

            fs.writeFileSync('/sys/class/gpio/gpio42/direction', 
                new Buffer('out\n'));

            chai.expect(gpio.direction())
                .to.equal(GPIO.OUT);
        });

    });

    describe('gpio.direction(value)', function() {

        it('should set the value to IN', function() {
            var gpio = new GPIO(42).direction(GPIO.IN)

            var value = fs.readFileSync('/sys/class/gpio/gpio42/direction');
        
            chai.expect(value.toString())
                .to.equal('in\n');
        });

        it('should set the value to OUT', function() {
            var gpio = new GPIO(42).direction(GPIO.OUT)

            var value = fs.readFileSync('/sys/class/gpio/gpio42/direction');
        
            chai.expect(value.toString())
                .to.equal('out\n');
        });

    });

});
