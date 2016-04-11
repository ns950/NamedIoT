/home/ndn/git/FIA/IoT/build/examples/runner -i 31 -l "running at node 3 of ambulance 1" -o 11 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 3" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 32 -l "running at node 3 of ambulance 2" -o 11 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 3" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 33 -l "running at node 3 of ambulance 3" -o 11 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 3" -d &

curl -H "Content-Type: application/json" -X POST -d '{"name":"h3","info":"runners 31, 32, 33","position":1,"edges":[2,4,8]}' http://hasnae:9000/api/nodes
