#!/bin/bash

log_file="ftp_log.txt"
hostname=$(hostname)

# Ensure the log file exists
touch "$log_file"

log_command() {
    user=$(whoami)
    time=$(date "+%Y-%m-%d %H:%M:%S")
    command=$(history 1 | sed 's/^[ ]*[0-9]\+[ ]*//')

    # Check if the command starts with "ftp"
    if [[ $command == ftp* ]]; then
        echo "[$time] Server: $hostname User: $user Command: $command" >> "$log_file"
    fi
}

# Set the PROMPT_COMMAND to log each command
export PROMPT_COMMAND=log_command

