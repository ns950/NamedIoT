/home/ndn/git/FIA/IoT/build/examples/runner -i 121 -l "running at node 12 of ambulance 1" -o 61 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 12" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 123 -l "running at node 12 of ambulance 3" -o 63 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 12" -d &

/home/ndn/git/FIA/IoT/build/examples/Facility -n /ndn/edu/h12/H2 -l Hospital -d > node.log

curl -H "Content-Type: application/json" -X POST -d '{"name":"h12","info":"runners 121, 123","position":12,"edges":[7,11,13,17]}' http://hasnae:9000/api/nodes
