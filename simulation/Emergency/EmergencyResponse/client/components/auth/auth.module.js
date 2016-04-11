'use strict';

angular.module('emergencyResponseApp.auth', [
  'emergencyResponseApp.constants',
  'emergencyResponseApp.util',
  'ngCookies',
  'ui.router'
])
  .config(function($httpProvider) {
    $httpProvider.interceptors.push('authInterceptor');
  });
