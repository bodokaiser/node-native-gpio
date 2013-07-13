var fs     = require('fs');
var util   = require('util');

var IN  = 'in\n';
var OUT = 'out\n';

var LOW  = '0\n';
var HIGH = '1\n';

var EXPORT_PATH    = '/sys/class/gpio/export';
var UNEXPORT_PATH  = '/sys/class/gpio/unexport';
var VALUE_PATH     = '/sys/class/gpio/gpio%d/value';
var DIRECTION_PATH = '/sys/class/gpio/gpio%d/direction';
var DIRECTORY_PATH = '/sys/class/gpio/gpio%d';

function export2(pin) {
    if (pin < 0 && pin > 100) {
        throw new Error('Pin must be a number in range.');
    }

    if (exported(pin)) return;
    
    var chunk = new Buffer(pin.toString());

    return fs.writeFileSync(EXPORT_PATH, chunk);
};

function unexport(pin) {
    if (pin < 0 && pin > 100) {
        throw new Error('Pin must be a number in range.');
    }

    if (!exported(pin)) return;

    var chunk = new Buffer(pin.toString());

    return fs.writeFileSync(UNEXPORT_PATH, chunk);
};

function exported(pin) {
    if (pin < 0 && pin > 100) {
        throw new Error('Pin must be a number in range.');
    }
    
    var path = util.format(DIRECTORY_PATH, pin);

    return fs.existsSync(path);   
};

function getValue(pin) {
    if (!exported(pin)) {
        throw new Error(util.format('Did not found GPIO pin %d.', pin));
    }
    
    var path = util.format(VALUE_PATH, pin);

    return fs.readFileSync(path).toString();
};

function setValue(pin, value) {
    if (!exported(pin)) {
        throw new Error(util.format('Did not found GPIO pin %d.', pin));
    }
    
    if (value != LOW && value != HIGH) {
        throw new Error('GPIO value must be either LOW or HIGH.');
    }
 
    if (getDirection(pin) != OUT) {
        throw new Error('GPIO value cannot be set when direction not OUT');
    }

    var path = util.format(VALUE_PATH, pin);

    return fs.writeFileSync(path, new Buffer(value));
};

function getDirection(pin) {
    if (!exported(pin)) {
        throw new Error(util.format('Did not found GPIO pin %d.', pin));
    }
    
    var path = util.format(DIRECTION_PATH, pin);

    return fs.readFileSync(path).toString();
};

function setDirection(pin, value) {
    if (!exported(pin)) {
        throw new Error(util.format('Did not found GPIO pin %d.', pin));
    }
    
    if (value != IN && value != OUT) {
        throw new Error('GPIO value must be either IN or OUT.');
    }

    var path = util.format(DIRECTION_PATH, pin);

    return fs.writeFileSync(path, new Buffer(value));
};

exports.IN           = IN;
exports.OUT          = OUT;
exports.LOW          = LOW;
exports.HIGH         = HIGH;

exports.export       = export2;
exports.unexport     = unexport;
exports.exported     = exported;
exports.getValue     = getValue;
exports.setValue     = setValue;
exports.getDirection = getDirection;
exports.setDirection = setDirection;
