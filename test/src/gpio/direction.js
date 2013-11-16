var fs   = require('fs');
var chai = require('chai');

module.exports = function(GPIO) {

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

};
