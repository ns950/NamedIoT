/home/ndn/git/FIA/IoT/build/examples/runner -i 131 -l "running at node 13 of ambulance 1" -o 181 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 13" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 132 -l "running at node 13 of ambulance 2" -o 83 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 13" -d &


curl -H "Content-Type: application/json" -X POST -d '{"name":"h13","info":"runners 131, 132","position":13,"edges":[8,12,14,18]}' http://hasnae:9000/api/nodes
