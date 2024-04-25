#!/bin/bash

# Define the command to monitor
MONITORED_COMMAND="ftp"

# Define the log file
LOG_FILE="ftp_logs.txt"

# Associative array to track last checked command history modification time
declare -A last_checked

# Function to get timestamp
get_timestamp() {
    date +"%Y-%m-%d %T"
}

# Function to log command attempts
log_command_attempt() {
    local timestamp=$(get_timestamp)
    local user="$1"
    local command="$2"

    echo "[$timestamp] User $user executed command: $command" >> "$LOG_FILE"
}

# Function to monitor commands in real-time
monitor_commands() {
    local user last_mod_time
    while true; do
        # Monitor all active terminals for the specified command
        for terminal in $(who | awk '{print $1}' | sort -u); do
            user="$terminal"
            last_mod_time=$(stat -c %Y "/home/$user/.bash_history")

            # Check if command history was modified since last check
            if [ "${last_checked[$user]}" != "$last_mod_time" ]; then
                last_checked[$user]="$last_mod_time"

                # Check for the monitored command in the user's command history
                if grep -q "\<$MONITORED_COMMAND\>" "/home/$user/.bash_history"; then
                    log_command_attempt "$user" "$MONITORED_COMMAND"
                fi
            fi
        done
        sleep 1  # Adjust the sleep interval as needed
    done
}

# Main function
main() {
    # Initialize last checked time for each user
    for user in $(who | awk '{print $1}' | sort -u); do
        last_checked["$user"]=$(stat -c %Y "/home/$user/.bash_history")
    done

    # Start monitoring commands
    monitor_commands
}

# Execute the main function
main

