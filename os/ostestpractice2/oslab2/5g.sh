#!/usr/bin/bash

command=$1

echo $command

ps -aux | grep '$command' | cut -d ' ' -f 1