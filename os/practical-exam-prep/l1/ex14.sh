#!/bin/bash

# Use find command to search for files with group write permission
find . -type d -perm -g=w -print

