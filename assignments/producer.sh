#!/bin/bash

if [ ! $1 ]; then
	echo "Usage: $0 <linepipe name>"
	exit 1
fi

# Students: When testing your character device, change this to test for the presence of your character device
if [[ ! -p $1 ]]; then
    echo $1 "not present OR not a pipe"
    exit 1
fi

for i in {1..100}
do
    line="Producer $$ Line $i" 
    echo "Writing: $line"
    echo $line >$1
    sleep 1
done


