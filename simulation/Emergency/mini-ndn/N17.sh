/home/ndn/git/FIA/IoT/build/examples/runner -i 171 -l "running at node 17 of ambulance 1" -o 121 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 17" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 173 -l "running at node 17 of ambulance 3" -o 123 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 17" -d &

curl -H "Content-Type: application/json" -X POST -d '{"name":"h17","info":"runners 171,173","position":17,"edges":[12,16,18,22]}' http://hasnae:9000/api/nodes
