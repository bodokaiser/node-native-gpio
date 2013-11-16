var chai = require('chai');

module.exports = function(GPIO) {

    describe('IN', function() {

        it('should equal "0"', function() {
            chai.expect(GPIO.IN)
                .to.equal(0);
        });

    });

    describe('OUT', function() {

        it('should equal "1"', function() {
            chai.expect(GPIO.OUT)
                .to.equal(1);
        });

    });

    describe('LOW', function() {

        it('should equal "0"', function() {
            chai.expect(GPIO.LOW)
                .to.equal(0);
        });

    });

    describe('HIGH', function() {

        it('should equal "1"', function() {
            chai.expect(GPIO.HIGH)
                .to.equal(1);
        });

    });

};
