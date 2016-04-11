/home/ndn/git/FIA/IoT/build/examples/runner -i 11 -l "running at node 1 of ambulance 1" -o 21 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A1 -l Ambulance -u http://localhost:9000/api/things -p 1" -d &

/home/ndn/git/FIA/IoT/build/examples/runner -i 13 -l "running at node 1 of ambulance 3" -o 23 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 1" -d &

curl -H "Content-Type: application/json" -X POST -d '{"name":"h1","info":"runners 11, 13, user","position":1,"edges":[2,6]}' http://localhost:3000/api/login