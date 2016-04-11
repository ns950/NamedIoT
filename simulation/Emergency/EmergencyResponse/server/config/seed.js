/**
 * Populate DB with sample data on server start
 * to disable, edit config/environment/index.js, and set `seedDB: false`
 */

'use strict';
import Node from '../api/node/node.model';
import Thing from '../api/thing/thing.model';
import User from '../api/user/user.model';

Thing.find({}).removeAsync()
  .then(() => {
    Thing.create({
        name: 'Ambulance 1',
        info: 'Vehicle for transportation of sick or injured people to, from or between places of treatment for an illness or injury',
        position : 1,
        type: 'Ambulance'
      },
      {
        name: 'Hospital 1',
        info: 'Health care institution providing patient treatment with specialized staff and equipment',
        position : 2,
        type: 'Hospital'
      },
      {
        name: 'Control Center 1',
        info: 'Building or room where control room operators receive incoming telephone calls from members of the public in need of assistance',
        position : 3,
        type: 'Center'
      });

  });
Node.find({}).removeAsync()
  .then(() => {

    Node.create({
        name: 'Node 1',
        info: 'Zone 1',
        position: 1,
        edges:[2,3]
      },
      {
        name: 'Node 2',
        info: 'Zone 2',
        position: 2,
        edges:[3]
      },
      {
        name: 'Node 3',
        info: 'Zone 3',
        position: 3,
        edges:[1]
      });
  });

User.find({}).removeAsync()
  .then(() => {
    User.createAsync({
      provider: 'local',
      name: 'Test User',
      email: 'test@example.com',
      password: 'test'
    }, {
      provider: 'local',
      role: 'admin',
      name: 'Admin',
      email: 'admin@example.com',
      password: 'admin'
    })
    .then(() => {
      console.log('finished populating users');
    });
  });
