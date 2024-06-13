#!/bin/bash

# Verifică dacă sunt furnizate argumente
if [ $# -eq 0 ]; then
    echo "Te rog să furnizezi cel puțin un nume de director."
    exit 1
fi

max_txt_count=-1
max_txt_dir=""

# Funcție recursivă pentru a număra fișierele .txt într-un director și subdirectoarele sale
count_txt_files() {
    local dir=$1
    local count=0

    for item in "$dir"/*; do
        if [ -d "$item" ]; then
            count=$((count + $(count_txt_files "$item")))
        elif [[ "$item" == *.txt ]]; then
            count=$((count + 1))
        fi
    done

    echo $count
}

# Parcurge toate argumentele (directoarele)
for dir in "$@"; do
    if [ -d "$dir" ]; then
        txt_count=$(count_txt_files "$dir")
        echo "Directorul '$dir' conține $txt_count fișiere .txt"
        
        # Verifică dacă acesta este directorul cu cele mai multe fișiere .txt
        if [ "$txt_count" -gt "$max_txt_count" ]; then
            max_txt_count=$txt_count
            max_txt_dir=$dir
        fi
    else
        echo "'$dir' nu este un director valid."
    fi
done

# Afișează directorul cu cele mai multe fișiere .txt
if [ "$max_txt_count" -ne -1 ]; then
    echo "Directorul cu cele mai multe fișiere .txt este '$max_txt_dir' cu $max_txt_count fișiere."
else
    echo "Nu s-au găsit fișiere .txt în directoarele specificate."
fi
