'use strict';

(function() {

class MainController {

  constructor($http, $scope, socket) {
    this.$http = $http;
    this.things = [];

    $http.get('/api/things').then(response => {
      this.things = response.data;
      socket.syncUpdates('thing', this.things);
    });

    $scope.$on('$destroy', function() {
      socket.unsyncUpdates('thing');
    });

    this.nodes = [];

    $http.get('/api/nodes').then(response => {
      this.nodes = response.data;
      socket.syncUpdates('node', this.nodes);
      //$scope.nodesDataSet = ;
    });

    $scope.$on('$destroy', function() {
      socket.unsyncUpdates('node');
    });


    var options = {

      height: "400px",
      width: '100%',
      nodes: {
        shape: 'dot',
        size: 20,
        font: {
          size: 15,
          color: '#ffffff'
        },
        borderWidth: 2
      },
      edges: {
        width: 2
      },
      groups: {
        Ambulance: {
          color: {background:'red',border:'white'},
          shape: 'diamond'
        },
        Hospital: {
          label: "I'm a dot!",
          shape: 'dot',
          color: 'cyan'
        },
        Center: {color:'rgb(0,255,140)'},
        icons: {
          shape: 'icon',
          icon: {
            face: 'FontAwesome',
            code: '\uf0c0',
            size: 50,
            color: 'orange'
          }
        },
        source: {
          color:{border:'white'}
        }
      }
    };

    $scope.options = angular.extend(options, {})

    $scope.onSelect = function (items) {
      // debugger;
      alert('select');
    };

    $scope.onClick = function (props) {
      //debugger;
      alert('Click');
    };

    $scope.onDoubleClick = function (props) {
      // debugger;
      alert('DoubleClick');
    };

    $scope.rightClick = function (props) {
      alert('Right click!');
      props.event.preventDefault();
    };

    $scope.events = {
      rangechange: $scope.onRangeChange,
      rangechanged: $scope.onRangeChanged,
      onload: $scope.onLoaded,
      select: $scope.onSelect,
      click: $scope.onClick,
      doubleClick: $scope.onDoubleClick,
      contextmenu: $scope.rightClick
    };

  }

  addThing() {
    if (this.newThing) {
      this.$http.post('/api/things', { name: this.newThing });
      this.newThing = '';
    }
  }

  deleteThing(thing) {
    this.$http.delete('/api/things/' + thing._id);
  }

  addNode() {
    if (this.newNode) {
      this.$http.post('/api/nodes', { name: this.newNode.name, position: this.newNode.position, edges: [this.newNode.edgef, this.newNode.edget]});
      this.newNode = {};
    }
  }

  deleteNode(node) {
    this.$http.delete('/api/nodes/' + node._id);
  }
}

angular.module('emergencyResponseApp')
  .controller('MainController', MainController);

})();
