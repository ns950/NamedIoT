/home/ndn/git/FIA/IoT/build/examples/runner -i 152 -l "running at node 15 of ambulance 2" -o 202 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 15" -d &
/home/ndn/git/FIA/IoT/simulation/runner -i 153 -l "running at node 15 of ambulance 3" -o 203 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 15" -d &

curl -H "Content-Type: application/json" -X POST -d '{"name":"h15","info":"runners 152, 153","position":15,"edges":[10,14,20]}' http://hasnae:9000/api/nodes
