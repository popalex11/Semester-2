#include "Duration.h"
#include <iostream>

Duration::Duration() : minutes(3), seconds(0) {}

Duration::Duration(int m, int s) {
    if (m < 1 || m > 10 || s < 0 || s >= 60) {
        throw std::invalid_argument("Invalid duration values.");
    }

    minutes = m;
    seconds = s;
}

Duration Duration::operator-(const Duration& other) const {
    int totalSeconds1 = minutes * 60 + seconds;
    int totalSeconds2 = other.minutes * 60 + other.seconds;

    int diffSeconds = std::abs(totalSeconds1 - totalSeconds2);
    if (diffSeconds < 0) {
        diffSeconds = 0;
    }

    int diffMinutes = diffSeconds / 60;
    diffSeconds %= 60;

    return Duration(diffMinutes, diffSeconds);
}
