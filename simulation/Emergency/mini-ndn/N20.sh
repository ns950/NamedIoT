/home/ndn/git/FIA/IoT/build/examples/runner -i 202 -l "running at node 20 of ambulance 2" -o 242 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 20" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 203 -l "running at node 20 of ambulance 3" -o 253 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 20" -d &


curl -H "Content-Type: application/json" -X POST -d '{"name":"h20","info":"runners 202,203","position":20,"edges":[15,19,25]}' http://hasnae:9000/api/nodes
