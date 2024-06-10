BEGIN {
    i = 0
}

/class/ {
    freq[$2] = 0
    line[$2] = ""
}

// {
    if ($1 in freq) {
        freq[$1]++
        line[$1] += NR
    }
}

END {
    for (i in freq) {
        printf("%s : %d\n", i, freq[i])
        print line[i]
    }
}