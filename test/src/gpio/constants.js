var should = require('should');

module.exports = function(GPIO) {

    it('IN should equal "0"', function() {
        GPIO.IN.should.equal(0);
    });

    it('OUT should equal "1"', function() {
        GPIO.OUT.should.equal(1);
    });

    it('LOW should equal "0"', function() {
        GPIO.LOW.should.equal(0);
    });

    it('HIGH should equal "1"', function() {
        GPIO.HIGH.should.equal(1);
    });

};
