/home/ndn/git/FIA/IoT/build/examples/runner -i 61 -l "running at node 6 of ambulance 1" -o 11 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 6" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 63 -l "running at node 6 of ambulance 3" -o 13 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 6" -d &

curl -H "Content-Type: application/json" -X POST -d '{"name":"h6","info":"runners 62,63","position":6,"edges":[1,7,11]}' http://hasnae:9000/api/nodes
