/home/ndn/git/FIA/IoT/build/examples/runner -i 42 -l "running at node 4 of ambulance 2" -o 52 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 4" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 43 -l "running at node 4 of ambulance 3" -o 53 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 4" -d &


curl -H "Content-Type: application/json" -X POST -d '{"name":"h4","info":"runners 42,43","position":4,"edges":[3,5,9]}' http://hasnae:9000/api/nodes
