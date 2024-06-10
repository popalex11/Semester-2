BEGIN {
    i = 0
}

/.* .*\(.*\)/ {
    split($2, tokens, "(")
    array[i] = tokens[1]
    freq[tokens[1]] = 0
    i++
}

// {
    split($0, tokens, " ")
    for(k=1;k<=length(tokens);k++) {
        split(tokens[k], new_tokens, "(")
        for (j=0;j<i;j++) {
            if (new_tokens[1] == array[j])
                freq[array[j]]++
        }
    }
}

END {
    for (j=0;j<i;j++) {
        freq[array[j]]--
        printf("%s : %s\n", array[j], freq[array[j]])
    }
}