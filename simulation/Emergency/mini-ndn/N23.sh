/home/ndn/git/FIA/IoT/build/examples/runner -i 231 -l "running at node 23 of ambulance 1" -o 221 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 23" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 232 -l "running at node 23 of ambulance 2" -o 182 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 23" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 233 -l "running at node 23 of ambulance 3" -o 223 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 23" -d &


curl -H "Content-Type: application/json" -X POST -d '{"name":"h23","info":"runners 231, 232, 233","position":23,"edges":[18,22,24]}' http://hasnae:9000/api/nodes
