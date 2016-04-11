/home/ndn/git/FIA/IoT/build/examples/runner -i 102 -l "running at node 10 of ambulance 2" -o 152 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A2 -l Ambulance -u http://localhost:9000/api/things -p 10" -d &
/home/ndn/git/FIA/IoT/build/examples/runner -i 103 -l "running at node 10 of ambulance 3" -o 153 -t 20 -s "/home/ndn/git/FIA/IoT/build/examples/Facility -n /A3 -l Ambulance -u http://localhost:9000/api/things -p 10" -d &

curl -H "Content-Type: application/json" -X POST -d '{"name":"h10","info":"runners 102, 103","position":10,"edges":[5,9,15]}' http://localhost:3000/api/login