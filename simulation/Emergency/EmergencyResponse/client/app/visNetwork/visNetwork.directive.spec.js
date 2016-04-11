'use strict';

describe('Directive: visNetwork', function () {

  // load the directive's module
  beforeEach(module('emergencyResponseApp'));

  var element,
    scope;

  beforeEach(inject(function ($rootScope) {
    scope = $rootScope.$new();
  }));

  it('should make hidden element visible', inject(function ($compile) {
    element = angular.element('<vis-network></vis-network>');
    element = $compile(element)(scope);
    //expect(element.text()).toBe('this is the visNetwork directive');
  }));
});
