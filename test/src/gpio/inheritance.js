var util   = require('util');
var should = require('should');

module.exports = function(GPIO) {
    
    function Device(id) {
        this.foo = null;

        GPIO.call(this, id);
    }
        
    util.inherits(Device, GPIO);

    it.skip('should be possible to inherit from GPIO', function() {
        var device = new Device(68);

        device.should.have.property('foo');
        device.should.have.property('value');
        device.should.have.property('direction');

        device
            .direction(GPIO.OUT)
            .value(GPIO.LOW)
            .value(GPIO.HIGH)
            ;
    });

};
