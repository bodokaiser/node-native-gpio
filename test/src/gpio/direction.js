var fs     = require('fs');
var should = require('should');

var IN  = 'in\n';
var OUT = 'out\n';

var DIRECTION = '/sys/class/gpio/gpio42/direction';

module.exports = function(GPIO) {

    describe('gpio.direction([direction])', function() {

        it('should return "IN" for direction', function(done) {
            var gpio = new GPIO(42);

            fs.writeFile(DIRECTION, IN, function(err) {
                if (err) throw err;

                gpio.direction().should.equal(GPIO.IN);

                done();
            });
        });

        it('should return "OUT" for direction', function(done) {
            var gpio = new GPIO(42);

            fs.writeFile(DIRECTION, OUT, function(err) {
                if (err) throw err;

                gpio.direction().should.equal(GPIO.OUT);

                done();
            });
        });

        it('should set the value to IN', function(done) {
            var gpio = new GPIO(42).direction(GPIO.IN)

            fs.readFile(DIRECTION, function(err, buf) {
                if (err) throw err;

                buf.toString().should.equal(IN);

                done();
            });
        });

        it('should set the value to OUT', function(done) {
            var gpio = new GPIO(42).direction(GPIO.OUT)
            
            fs.readFile(DIRECTION, function(err, buf) {
                if (err) throw err;

                buf.toString().should.equal(OUT);

                done();
            });
        });

    });

};
