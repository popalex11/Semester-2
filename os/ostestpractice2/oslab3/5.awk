BEGIN {
    counter = 0
}

// {
    split($0, chars, "")
    if (length(chars) > 10) {
        counter++
        printf("%d ", NR)
        for (i=11;i<=length(chars);i++) {
            printf("%c", chars[i])
        }
        printf("\n")
    }
}

END {
    printf("\n%d, %s\n", counter, FILENAME)
}