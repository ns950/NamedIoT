'use strict';

angular.module('emergencyResponseApp')
  .factory('VisDataSet', function () {
    'use strict';
    return function (data, options) {
      var rawNodes = [];
      var rawEdges = [];
      data.forEach( function (node)
      {
        rawNodes.push({id: node.position, label: node.name});
        node.edges.forEach( function (edge){
          rawEdges.push({from: node.position, to: edge});
        });
      });
      var retData = {
        nodes: new vis.DataSet(rawNodes),
        edges: new vis.DataSet(rawEdges)
      };
      //var ret  = new vis.DataSet(retData, options);
      console.log(JSON.stringify(retData));
      // Create the new dataSets
      return retData;
    };
/*    // Service logic
    // ...

    var meaningOfLife = 42;

    // Public API here
    return {
      someMethod: function () {
        return meaningOfLife;
      }
    };*/
  });

