// {
    split($0, chars, " ")
    for (i=0;i<length(chars);i++) {
        freq[chars[i]]++
        print freq[chars[i]]
    }
}