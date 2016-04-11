/home/ndn/git/FIA/IoT/build/examples/runner -i 221 -l "running at node 22 of ambulance 1" -o 171 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 22" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 223 -l "running at node 22 of ambulance 3" -o 173 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 22" -d &

curl -H "Content-Type: application/json" -X POST -d '{"name":"h22","info":"runners 221, 223","position":22,"edges":[17,21,23]}' http://hasnae:9000/api/nodes
