/home/ndn/git/FIA/IoT/build/examples/runner -i 81 -l "running at node 8 of ambulance 1" -o 131 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 8" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 82 -l "running at node 8 of ambulance 2" -o 32 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 8" -d &


curl -H "Content-Type: application/json" -X POST -d '{"name":"h8","info":"runners 81,82","position":8,"edges":[3,7,9,13}' http://hasnae:9000/api/nodes
