/home/ndn/git/FIA/IoT/build/examples/runner -i 242 -l "running at node 24 of ambulance 2" -o 232 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 24" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 243 -l "running at node 24 of ambulance 3" -o 233 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 24" -d &


curl -H "Content-Type: application/json" -X POST -d '{"name":"h24","info":"runners 242, 243","position":24,"edges":[19,23,25]}' http://hasnae:9000/api/nodes
