'use strict';

var proxyquire = require('proxyquire').noPreserveCache();

var nodeCtrlStub = {
  index: 'nodeCtrl.index',
  show: 'nodeCtrl.show',
  create: 'nodeCtrl.create',
  update: 'nodeCtrl.update',
  destroy: 'nodeCtrl.destroy'
};

var routerStub = {
  get: sinon.spy(),
  put: sinon.spy(),
  patch: sinon.spy(),
  post: sinon.spy(),
  delete: sinon.spy()
};

// require the index with our stubbed out modules
var nodeIndex = proxyquire('./index.js', {
  'express': {
    Router: function() {
      return routerStub;
    }
  },
  './node.controller': nodeCtrlStub
});

describe('Node API Router:', function() {

  it('should return an express router instance', function() {
    nodeIndex.should.equal(routerStub);
  });

  describe('GET /api/nodes', function() {

    it('should route to node.controller.index', function() {
      routerStub.get
        .withArgs('/', 'nodeCtrl.index')
        .should.have.been.calledOnce;
    });

  });

  describe('GET /api/nodes/:id', function() {

    it('should route to node.controller.show', function() {
      routerStub.get
        .withArgs('/:id', 'nodeCtrl.show')
        .should.have.been.calledOnce;
    });

  });

  describe('POST /api/nodes', function() {

    it('should route to node.controller.create', function() {
      routerStub.post
        .withArgs('/', 'nodeCtrl.create')
        .should.have.been.calledOnce;
    });

  });

  describe('PUT /api/nodes/:id', function() {

    it('should route to node.controller.update', function() {
      routerStub.put
        .withArgs('/:id', 'nodeCtrl.update')
        .should.have.been.calledOnce;
    });

  });

  describe('PATCH /api/nodes/:id', function() {

    it('should route to node.controller.update', function() {
      routerStub.patch
        .withArgs('/:id', 'nodeCtrl.update')
        .should.have.been.calledOnce;
    });

  });

  describe('DELETE /api/nodes/:id', function() {

    it('should route to node.controller.destroy', function() {
      routerStub.delete
        .withArgs('/:id', 'nodeCtrl.destroy')
        .should.have.been.calledOnce;
    });

  });

});
