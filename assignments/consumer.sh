#!/bin/bash

if [ ! $1 ]; then
	echo "Usage: $0 <linepipe name>"
	exit 1
fi

if [[ ! -p $1 ]]; then
    # Students: when testing your character device implementation, replace the following line with your module insertion code 
    if   ! mkfifo $1; then
	exit 1
    fi
fi

while true
do
    if read line <$1; then
        echo $line
    fi
done

