'use strict';

describe('Service: VisDataSet', function () {

  // load the service's module
  beforeEach(module('emergencyResponseApp'));

  // instantiate service
  var VisDataSet;
  beforeEach(inject(function (_VisDataSet_) {
    VisDataSet = _VisDataSet_;
  }));

  it('should do something', function () {
    expect(!!VisDataSet).toBe(true);
  });

});
