#!/bin/bash
#CreateDir.bash

if [[  -s  $1  ]]; then
	mkdir $1
	echo "You got here"
fi
echo $1
echo "$1"
echo $2
echo "$2"