	#!/bin/bash

	log_file="ftp_log.txt"

	# Function to log ftp commands
	log_ftp_command() {
	    local user=$(whoami)
	    local time=$(date +"%Y-%m-%d %H:%M:%S")
	    local server=$(netstat -tn | awk '$6 == "ESTABLISHED" && $4 ~ /:21$/ {print $5}' | cut -d: -f1 | sort | uniq)
	    
	    echo "User: $user | Time: $time | Server: $server" >> "$log_file"
	}

	# Main loop to continuously monitor processes
	while true; do
	    ftp_processes=$(ps -eo user,cmd | grep "ftp" | grep -v grep)
	    if [ ! -z "$ftp_processes" ]; then
		log_ftp_command
	    fi
	    sleep 5  # Adjust the frequency of monitoring as needed
	done

