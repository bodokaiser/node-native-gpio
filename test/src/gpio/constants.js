var should = require('should');

module.exports = function(GPIO) {

    describe('IN', function() {

        it('should equal "0"', function() {
            GPIO.IN.should.equal(0);
        });

    });

    describe('OUT', function() {

        it('should equal "1"', function() {
            GPIO.OUT.should.equal(1);
        });

    });

    describe('LOW', function() {

        it('should equal "0"', function() {
            GPIO.LOW.should.equal(0);
        });

    });

    describe('HIGH', function() {

        it('should equal "1"', function() {
            GPIO.HIGH.should.equal(1);
        });

    });

};
