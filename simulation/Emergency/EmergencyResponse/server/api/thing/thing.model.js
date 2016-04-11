'use strict';

var mongoose = require('bluebird').promisifyAll(require('mongoose'));

var ThingSchema = new mongoose.Schema({
  name: String,
  info: String,
  active: { type: Boolean, default: false },
  type: String,
  position: Number
});

export default mongoose.model('Thing', ThingSchema);
