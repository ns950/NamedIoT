'use strict';

angular.module('emergencyResponseApp')
/**
 * Directive for network chart.
 */
.directive('visNetwork', function (VisDataSet) {
  return {
    restrict: 'EA',
    transclude: false,
    scope: {
      data: '=',
      options: '=?',
      events: '=?'
    },
    link: function (scope, element, attr) {
      var networkEvents = [
        'click',
        'doubleClick',
        'oncontext',
        'hold',
        'release',
        'selectNode',
        'selectEdge',
        'deselectNode',
        'deselectEdge',
        'dragStart',
        'dragging',
        'dragEnd',
        'hoverNode',
        'blurNode',
        'zoom',
        'showPopup',
        'hidePopup',
        'startStabilizing',
        'stabilizationProgress',
        'stabilizationIterationsDone',
        'stabilized',
        'resize',
        'initRedraw',
        'beforeDrawing',
        'afterDrawing',
        'animationFinished'

      ];

      var network = null;
      //scope.$watchGroup(['data', 'styles'], function(newValues, oldValues, scope){
      scope.$watch('data', function(newValue, oldValue) {
      //  if (newValues[0])
      //    console.log("I see a data change in Nodes!", newValues[0]);
      //  if (newValues[1])
      //    console.log("I see a data change in Things!", newValues[1]);
        // Sanity check
        if (scope.data == null) {
          return;
        }
        if (scope.options == null) {
          scope.options = {};
        }
        //console.log(JSON.stringify(scope.data));
        // If we've actually changed the data set, then recreate the graph
        // We can always update the data by adding more data to the existing data set
        if (network != null) {
          network.destroy();
        }
        //console.log(element[0]);
        // Create the graph2d object
        network = new vis.Network(element[0], VisDataSet(scope.data), scope.options);
        //console.log(network.body);
        // Attach an event handler if defined
        angular.forEach(scope.events, function (callback, event) {
          if (networkEvents.indexOf(String(event)) >= 0) {
            network.on(event, callback);
          }
        });

        // onLoad callback
        if (scope.events != null && scope.events.onload != null &&
          angular.isFunction(scope.events.onload)) {
          scope.events.onload(network);
        }
      }, true);

      scope.$watchCollection('options', function (options) {
        if (network == null) {
          return;
        }
        network.setOptions(options);
      });
    }
  };
});
