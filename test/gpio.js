var fs       = require('fs');
var chai     = require('chai');
var nativeio = require('../lib');

describe('gpio', function() {

    var gpio = nativeio.gpio;

    var exportPath   = '/sys/class/gpio/export';
    var unexportPath = '/sys/class/gpio/unexport';

    var mockupOneNum = 42;
    var mockupTwoNum = 36;
    var mockupOneStr = new Buffer('42');
    var mockupTwoStr = new Buffer('36');

    var mockupOnePath          = '/sys/class/gpio/gpio42';
    var mockupOnePathValue     = '/sys/class/gpio/gpio42/value';
    var mockupOnePathDirection = '/sys/class/gpio/gpio42/direction';
    var mockupTwoPath          = '/sys/class/gpio/gpio36';
    var mockupTwoPathValue     = '/sys/class/gpio/gpio36/value';
    var mockupTwoPathDirection = '/sys/class/gpio/gpio36/direction';

    describe('IN', function() {

        it('should equal "in\/n"', function() {
            chai.expect(gpio.IN)
                .to.equal('in\n');
        });

    });

    describe('OUT', function() {

        it('should equal "out\/n"', function() {
            chai.expect(gpio.OUT)
                .to.equal('out\n');
        });

    });

    describe('LOW', function() {

        it('should equal "0\/n"', function() {
            chai.expect(gpio.LOW)
                .to.equal('0\n');
        });

    });

    describe('HIGH', function() {

        it('should equal "1\/n"', function() {
            chai.expect(gpio.HIGH)
                .to.equal('1\n');
        });

    });

    describe('export(pin)', function() {

        it('should export a gpio pin', function() {
            gpio.export(mockupOneNum);

            var exists = fs.existsSync(mockupOnePath);

            chai.expect(exists).to.be.true;
        });

    });

    describe('unexport(pin)', function() {

        it('should unexport a gpio pin', function() {
            gpio.unexport(mockupTwoNum);

            var exists = fs.existsSync(mockupTwoPath);

            chai.expect(exists).to.be.false;
        });

    });

    describe('exported(pin)', function() {

        it('should return "true" for exported', function() {
            if (!fs.existsSync(mockupOnePath)) 
                fs.writeFileSync(exportPath, mockupOneStr);

            var exported = gpio.exported(mockupOneNum);
            
            var exists = fs.existsSync(mockupOnePath);
            
            chai.expect(exported).to.equal(exists);
        });

        it('should return "false" for unexported', function() {
            if (fs.existsSync(mockupTwoPath)) 
                fs.writeFileSync(unexportPath, mockupTwoStr);

            var exported = gpio.exported(mockupTwoNum);
            
            var exists = fs.existsSync(mockupTwoPath);

            chai.expect(exported).to.equal(exists);
        });

    });

    describe('getValue(pin)', function() {

        it('should return value of gpio value', function(done) {
            gpio.export(mockupOneNum);

            var value = gpio.getValue(mockupOneNum);

            fs.readFile(mockupOnePathValue, function(err, result) {
                chai.expect(err).to.not.exist;
                chai.expect(result.toString())
                    .to.equal(value);

                done();
            });
        });

    });

    describe('setValue(pin, value)', function() {

        it('should set value of gpio to "LOW"', function(done) {
            gpio.export(mockupOneNum);

            gpio.setDirection(mockupOneNum, gpio.OUT);
            
            gpio.setValue(mockupOneNum, gpio.LOW);

            fs.readFile(mockupOnePathValue, function(err, result) {
                chai.expect(err).to.not.exist;
                chai.expect(result.toString())
                    .to.equal(gpio.LOW);

                done();
            });
        });

        it('should set value of gpio to "HIGH"', function(done) {
            gpio.export(mockupTwoNum);

            gpio.setDirection(mockupTwoNum, gpio.OUT);
            
            gpio.setValue(mockupTwoNum, gpio.HIGH);

            fs.readFile(mockupTwoPathValue, function(err, result) {
                chai.expect(err).to.not.exist;
                chai.expect(result.toString())
                    .to.equal(gpio.HIGH);

                done();
            });
        });

    });

    describe('getDirection(pin)', function() {

        it('should return value of gpio direction', function(done) {
            gpio.export(mockupOneNum);

            var direction = gpio.getDirection(mockupOneNum);

            fs.readFile(mockupOnePathDirection, function(err, result) {
                chai.expect(err).to.not.exist;
                chai.expect(result.toString())
                    .to.equal(direction);

                done();
            });
        });

    });

    describe('setDirection(pin, value)', function() {

        it('should set value of gpio direction to "IN"', function(done) {
            gpio.export(mockupOneNum);
            
            gpio.setDirection(mockupOneNum, gpio.IN);

            fs.readFile(mockupOnePathDirection, function(err, result) {
                chai.expect(err).to.not.exist;
                chai.expect(result.toString())
                    .to.equal(gpio.IN);

                done();
            });
        });

        it('should set value of gpio direction to "OUT"', function(done) {
            gpio.export(mockupTwoNum);

            gpio.setDirection(mockupTwoNum, gpio.OUT);

            fs.readFile(mockupTwoPathDirection, function(err, result) {
                chai.expect(err).to.not.exist;
                chai.expect(result.toString())
                    .to.equal(gpio.OUT);

                done();
            });
        });

    });

});
