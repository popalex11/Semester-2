BEGIN {
    i = 0
    values[0] = 1
    freq[0] = 0
}

// {
    print $0
    if ($0 not in values) {
        freq[$0] = 0
        values[i] = $0 
        i++
    }
    freq[$0]++
}

END {
}