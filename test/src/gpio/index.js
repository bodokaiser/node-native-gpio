var GPIO = require('../../../build/Release/gpio');

describe('GPIO', function() {

    require('./constants')(GPIO);

    require('./constructor')(GPIO);

    require('./direction')(GPIO);

    require('./value')(GPIO);
   
});
