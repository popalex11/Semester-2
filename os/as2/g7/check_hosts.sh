#!/bin/bash

# Check if no arguments are provided
if [ $# -eq 0 ]; then
  echo "Usage: $0 hostname1 hostname2 hostname3 ..."
  exit 1
fi


for hostname in "$@"; do

  if ping -c 1 "$hostname" > /dev/null 2> /dev/null | grep -q "64 bytes" ; then 
    echo "$hostname is alive."
  else
    echo "$hostname is not reachable."
  fi
done




