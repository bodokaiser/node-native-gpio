var GPIO = require('../../../build/Release/gpio');

describe('GPIO', function() {

    require('./constants')(GPIO);

    require('./new')(GPIO);

    require('./value')(GPIO);

    require('./direction')(GPIO);
   
});
