#ifndef SONG_H
#define SONG_H

#include <iostream>
#include "Duration.h"

class Song {
private:
    std::string title;
    std::string artist;
    unsigned short characteristics[5];
    Duration duration;

    static unsigned short defaultCharacteristics[5];
    static Duration defaultDuration;

public:
    Song();
    Song(std::string title, std::string artist, unsigned short characs[], Duration d);

    static void setDefaultCharacteristics(unsigned short characs[]);
    static void resetDefaultCharacteristics();
    static void setDefaultDuration(Duration d);

    void printInfo() const;
    double calculateSimilarity() const;
    int calculateDurationDifferenceInSeconds(const Song& other) const;

    Duration getDuration() const { return duration; }
};

#endif  // SONG_H
