/home/ndn/git/FIA/IoT/build/examples/runner -i 52 -l "running at node 5 of ambulance 2" -o 102 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 5" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 53 -l "running at node 5 of ambulance 3" -o 103 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 5" -d &


curl -H "Content-Type: application/json" -X POST -d '{"name":"h5","info":"runners 52,53","position":5,"edges":[4,10]}' http://hasnae:9000/api/nodes
