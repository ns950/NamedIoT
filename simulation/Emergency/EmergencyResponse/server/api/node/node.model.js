'use strict';

var mongoose = require('bluebird').promisifyAll(require('mongoose'));

var NodeSchema = new mongoose.Schema({
  name: String,
  info: String,
  active: { type: Boolean, default: false },
  position: Number,
  edges: [Number]
});

export default mongoose.model('Node', NodeSchema);
