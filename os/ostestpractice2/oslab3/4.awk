// {
    prev = ""
    found = 0
    for (i=1; i <= NF; i++) {
        if ($i == prev && !found) {
            found = 1
        }
        if (!found)
            prev = $i
    }
    if (found) {
        printf("%d %s : %s\n", NR, prev, $0)
    }
}