BEGIN {
    counter1 = 0
    counter2 = 0
}

// {
    split($0, chars, "")
    for ( i=1; i <= length($0); i++ ) {
        if ( chars[i] >= "A" && chars[i] <= "Z" )
            counter1++
        if ( chars[i] >= "a" && chars[i] <= "z" )
            counter2++
    }
}

END {
    print counter1 / counter2
}