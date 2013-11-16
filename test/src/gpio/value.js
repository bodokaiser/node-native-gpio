var fs   = require('fs');
var chai = require('chai');

module.exports = function(GPIO) {

    describe('gpio.value()', function() {

        it('should return "LOW" for value', function() {
            var gpio = new GPIO(42);

            fs.writeFileSync('/sys/class/gpio/gpio42/direction',
                new Buffer('out\n'));
            fs.writeFileSync('/sys/class/gpio/gpio42/value', 
                new Buffer('0\n'));

            chai.expect(gpio.value())
                .to.equal(GPIO.LOW);
        });

        it('should return "HIGH" for value', function() {
            var gpio = new GPIO(42);

            fs.writeFileSync('/sys/class/gpio/gpio42/direction',
                new Buffer('out\n'));
            fs.writeFileSync('/sys/class/gpio/gpio42/value', 
                new Buffer('1\n'));

            chai.expect(gpio.value())
                .to.equal(GPIO.HIGH);
        });

    });

    describe('gpio.value(value)', function() {

        it('should set the value to LOW', function() {
            var gpio = new GPIO(42)

            fs.writeFileSync('/sys/class/gpio/gpio42/direction', 
                new Buffer('out\n'));

            gpio.value(GPIO.LOW);

            var value = fs.readFileSync('/sys/class/gpio/gpio42/value');
        
            chai.expect(value.toString())
                .to.equal('0\n');
        });

        it('should set the value to HIGH', function() {
            var gpio = new GPIO(42);

            fs.writeFileSync('/sys/class/gpio/gpio42/direction', 
                new Buffer('out\n'));

            gpio.value(GPIO.HIGH);

            var value = fs.readFileSync('/sys/class/gpio/gpio42/value');
        
            chai.expect(value.toString())
                .to.equal('1\n');
        });

        it('should throw error if setting value on direction IN', function() {
            var gpio = new GPIO(42);
        
            fs.writeFileSync('/sys/class/gpio/gpio42/direction', 
                new Buffer('in\n'));

            chai.expect(function() {
                gpio.value(GPIO.LOW);
            }).to.throw(Error);
        });

    });

};
