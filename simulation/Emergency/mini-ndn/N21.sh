/home/ndn/git/FIA/IoT/build/examples/Facility -n /ndn/edu/h21/H3 -l ControlCenter -d > node.log


curl -H "Content-Type: application/json" -X POST -d '{"name":"h21","info":"hospital 3","position":21,"edges":[16,22]}' http://hasnae:9000/api/nodes
