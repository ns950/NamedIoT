/home/ndn/git/FIA/IoT/build/examples/runner -i 21 -l "running at node 2 of ambulance 1" -o 31 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 2" -d &

/home/ndn/git/FIA/IoT/build/examples/runner -i 23 -l "running at node 2 of ambulance 3" -o 33 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 2" -d &

curl -H "Content-Type: application/json" -X POST -d '{"name":"h2","info":"runners 21, 23","position":2,"edges":[1,3,7]}' http://hasnae:9000/api/nodes
