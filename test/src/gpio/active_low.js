var fs     = require('fs');
var should = require('should');

var LOW  = '0\n';
var HIGH = '1\n';

var ACTIVE_LOW = '/sys/class/gpio/gpio42/active_low';

module.exports = function(GPIO) {

    describe('gpio.activeLow([value])', function() {

        it('should return "LOW" for value', function(done) {
            var gpio = new GPIO(42);

            fs.writeFile(ACTIVE_LOW, LOW, function(err) {
                if (err) throw err;

                gpio.activeLow().should.equal(GPIO.LOW);

                done();
            });
        });

        it('should return "HIGH" for value', function(done) {
            var gpio = new GPIO(42);

            fs.writeFile(ACTIVE_LOW, HIGH, function(err) {
                if (err) throw err;

                gpio.activeLow().should.equal(GPIO.HIGH);

                done();
            });
        });
        
        it('should set the value to LOW', function(done) {
            new GPIO(42).activeLow(GPIO.LOW);
            
            fs.readFile(ACTIVE_LOW, function(err, buf) {
                if (err) throw err;

                buf.toString().should.equal(LOW);

                done();
            });
        });

        it('should set the value to HIGH', function(done) {
            new GPIO(42).activeLow(GPIO.HIGH);
            
            fs.readFile(ACTIVE_LOW, function(err, buf) {
                if (err) throw err;

                buf.toString().should.equal(HIGH);

                done();
            });
        });

    });

};
