var fs = require('fs');

fs.exists('/sys', function(result) {
    if (!result) {
        throw new Error('Did not found sysfs.');
    }
});

module.exports = require('../build/Release/gpio');
