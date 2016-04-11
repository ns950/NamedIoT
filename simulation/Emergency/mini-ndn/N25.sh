/home/ndn/git/FIA/IoT/build/examples/Facility -n /ndn/edu/h25/H4 -l ControlCenter -d > node.log

curl -H "Content-Type: application/json" -X POST -d '{"name":"h25","info":"hospital 4","position":25,"edges":[20,24]}' http://hasnae:9000/api/nodes
