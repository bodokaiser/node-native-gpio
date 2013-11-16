var fs   = require('fs');
var chai = require('chai');

module.exports = function(GPIO) {

    describe('new GPIO(id)', function() {

        it('should export a GPIO device', function() {
            var gpio = new GPIO(36);

            var exists = fs.existsSync('/sys/class/gpio/gpio36');

            chai.expect(exists)
                .to.equal.true;
        });

    });

};
