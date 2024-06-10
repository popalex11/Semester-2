#!/usr/bin/bash

for arg in $@
do
    word1=`cut -d ':' -f 3 $arg`
    word2=`cut -d ':' -f 1 $arg`
    sed 's/'"$word1"'/'"$word2"'/g; s/'"$word2"'/'"$word1"'/' $arg
done