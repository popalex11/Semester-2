BEGIN {
    counter = 0
}

// {
    split($0, chars, "")
    counter += length(chars)
}

END {
    printf("%s, %s", FILENAME, counter / NR)
}