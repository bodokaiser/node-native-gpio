var fs     = require('fs');
var should = require('should');

var PATH = '/sys/class/gpio/gpio36';

module.exports = function(GPIO) {

    describe('new GPIO(id)', function() {

        it('should export a GPIO device', function(done) {
            var gpio = new GPIO(36);

            fs.exists(PATH, function(exists) {
                exists.should.be.true;

                done();
            });
        });

    });

};
