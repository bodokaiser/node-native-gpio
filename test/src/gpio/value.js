var fs     = require('fs');
var should = require('should');

var IN  = 'in\n';
var OUT = 'out\n';

var LOW  = '0\n';
var HIGH = '1\n';

var VALUE     = '/sys/class/gpio/gpio42/value';
var DIRECTION = '/sys/class/gpio/gpio42/direction';

module.exports = function(GPIO) {

    describe('gpio.value([value])', function() {

        it('should return "LOW" for value', function(done) {
            var gpio = new GPIO(42);

            fs.writeFile(DIRECTION, OUT, function(err) {
                if (err) throw err;

                fs.writeFile(VALUE, LOW, function(err) {
                    if (err) throw err;

                    gpio.value().should.equal(GPIO.LOW);

                    done();
                });
            });
        });

        it('should return "HIGH" for value', function(done) {
            var gpio = new GPIO(42);

            fs.writeFile(DIRECTION, OUT, function(err) {
                if (err) throw err;

                fs.writeFile(VALUE, HIGH, function(err) {
                    if (err) throw err;

                    gpio.value().should.equal(GPIO.HIGH);

                    done();
                });
            });
        });
        
        it('should set the value to LOW', function(done) {
            fs.writeFile(DIRECTION, OUT, function(err) {
                if (err) throw err;
    
                new GPIO(42).value(GPIO.LOW);
                
                fs.readFile(VALUE, function(err, buf) {
                    if (err) throw err;

                    buf.toString().should.equal(LOW);

                    done();
                });
            });
        });

        it('should set the value to HIGH', function(done) {
            fs.writeFile(DIRECTION, OUT, function(err) {
                if (err) throw err;
    
                new GPIO(42).value(GPIO.HIGH);
                
                fs.readFile(VALUE, function(err, buf) {
                    if (err) throw err;

                    buf.toString().should.equal(HIGH);

                    done();
                });
            });
        });

        it('should throw error if setting value on direction IN', function(done) {
            fs.writeFile(DIRECTION, IN, function(err) {
                if (err) throw err;

                (function() {
                    new GPIO(42).value(GPIO.LOW);
                }).should.throwError();

                done();
            });
        });

    });

};
