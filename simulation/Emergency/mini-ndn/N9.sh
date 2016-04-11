/home/ndn/git/FIA/IoT/build/examples/Facility -n /ndn/edu/h9/H1 -l Hospital -u http://hasnae:9000/api/things -p 9 -d > node.log

curl -H "Content-Type: application/json" -X POST -d '{"name":"h8","info":"runners 81,82","position":8,"edges":[3,7,9,13}' http://hasnae:9000/api/nodes
