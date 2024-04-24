#!/bin/bash

# Define the log file
LOG_FILE="ftp_log.txt"

# Function to get timestamp
get_timestamp() {
    date +"%Y-%m-%d %T"
}

# Function to log ftp attempts
log_ftp_attempt() {
    local timestamp=$(get_timestamp)
    local user="$USER"
    local server="$SSH_CONNECTION"

    # Extract only the IP address from the SSH_CONNECTION variable
    local ip_address=$(echo "$server" | cut -d " " -f 1)

    echo "[$timestamp] User $user attempted to connect to FTP server $ip_address" >> "$LOG_FILE"
}

# Main function
main() {
    local ftp_executed=false

    # Monitor command usage using 'trap'
    trap 'if [ "$ftp_executed" = false ]; then log_ftp_attempt; ftp_executed=true; fi' DEBUG

    # Wait for the ftp command to finish
    echo "Waiting for FTP session to finish..."
    wait

    # Exit the monitoring loop
    echo "FTP session terminated. Exiting..."
    exit 0
}

# Execute the main function
main
