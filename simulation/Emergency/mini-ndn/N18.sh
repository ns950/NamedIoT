/home/ndn/git/FIA/IoT/build/examples/runner -i 181 -l "running at node 18 of ambulance 1" -o 231 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 18" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 182 -l "running at node 18 of ambulance 2" -o 132 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 18" -d &


curl -H "Content-Type: application/json" -X POST -d '{"name":"h18","info":"runners 181,182","position":18,"edges":[13,17,19,23]}' http://hasnae:9000/api/nodes
