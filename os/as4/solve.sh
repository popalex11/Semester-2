#!/bin/bash

LOG_FILE="ftp_log.txt"

# Function to intercept and log ftp commands
function intercept_ftp_command {
    local cmd="$1"
    local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    local server=$(netstat -ant | awk '$6 == "ESTABLISHED" && $4 ~ /:21$/ {print $5}' | awk -F ':' '{print $1}' | head -n 1)
    
    # Log the user, timestamp, and server
    echo "User: $(whoami), Time: $timestamp, Server: $server, Command: $cmd" >> "$LOG_FILE"
}

# Alias setup to intercept the ftp command
alias ftp="intercept_ftp_command"

# Continuously monitor for user commands
while true; do
    sleep 1 # Adjust sleep duration as needed
done

