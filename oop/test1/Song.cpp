#include <string>
#include <stdexcept>
#include <cmath>
#include "Song.h"
#include <iostream>
#include <random>

unsigned short Song::defaultCharacteristics[5] = {0, 0, 0, 0, 0};
Duration Song::defaultDuration;

Song::Song() : title("Title X"), artist("Artist Z") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> charDist(1, 100);

    for (int i = 0; i < 5; ++i) {
        unsigned short value = charDist(gen);
        characteristics[i] = value;
    }

    duration = defaultDuration;
}

Song::Song(std::string title, std::string artist, unsigned short characs[], Duration d)
    : title(title), artist(artist), duration(d) {
    for (int i = 0; i < 5; ++i) {
        characteristics[i] = characs[i];
    }
}

void Song::setDefaultCharacteristics(unsigned short characs[]) {
    for (int i = 0; i < 5; ++i) {
        if (characs[i] < 0 || characs[i] > 100) {
            throw std::invalid_argument("Characteristics must be between 0 and 100.");
        }
        defaultCharacteristics[i] = characs[i];
    }
}

void Song::resetDefaultCharacteristics() {
    for (int i = 0; i < 5; ++i) {
        defaultCharacteristics[i] = 0;
    }
}

void Song::setDefaultDuration(Duration d) {
    defaultDuration = d;
}

void Song::printInfo() const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "Characteristics: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << characteristics[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Duration: " << duration.getMinutes() << " minutes, "
              << duration.getSeconds() << " seconds" << std::endl;
}

double Song::calculateSimilarity() const {
    // Check if the song's duration is within 30 seconds of the default duration
    int durationDiff = std::abs(duration.getSeconds() - defaultDuration.getSeconds());
    if (duration.getMinutes() == defaultDuration.getMinutes() && durationDiff <= 30) {
        // Calculate cosine distance between the song's characteristics and default characteristics
        double dotProduct = 0;
        double normA = 0;
        double normB = 0;

        for (int i = 0; i < 5; ++i) {
            dotProduct += characteristics[i] * defaultCharacteristics[i];
            normA += characteristics[i] * characteristics[i];
            normB += defaultCharacteristics[i] * defaultCharacteristics[i];
        }

        normA = std::sqrt(normA);
        normB = std::sqrt(normB);

        if (normA == 0 || normB == 0) {
            return 0; // Return 0 if either norm is 0 to avoid division by zero
        }

        double cosineDistance = 1 - (dotProduct / (normA * normB));
        return cosineDistance;
    } else {
        return -1; // Duration not within 30 seconds, return -1
    }
}

int Song::calculateDurationDifferenceInSeconds(const Song& other) const {
    int totalSeconds1 = duration.getMinutes() * 60 + duration.getSeconds();
    int totalSeconds2 = other.duration.getMinutes() * 60 + other.duration.getSeconds();

    int diffSeconds = std::abs(totalSeconds1 - totalSeconds2);
    return diffSeconds;
}
