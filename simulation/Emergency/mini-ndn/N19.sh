
/home/ndn/git/FIA/IoT/build/examples/Facility -n /ndn/edu/h19/CC -l ControlCenter -d > node.log

curl -H "Content-Type: application/json" -X POST -d '{"name":"h19","info":"Control center","position":19,"edges":[14,18,20,24]}' http://hasnae:9000/api/nodes
