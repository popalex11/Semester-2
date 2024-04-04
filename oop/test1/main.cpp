#include <iostream>
#include "Song.h"
#include "Duration.h"

int main() {
    try {
        // Set default characteristics and duration
        unsigned short defaultChars[5] = {30, 40, 50, 60, 70};
        Duration defaultDuration(3, 30);
        Song::setDefaultCharacteristics(defaultChars);
        Song::setDefaultDuration(defaultDuration);

        // Create Song object stored on the stack
        unsigned short characs1[5] = {80, 50, 30, 70, 90};
        Duration duration1(3, 25);
        Song song1("Song Title 1", "Artist 1", characs1, duration1);

        // Create Song object stored on the heap
        unsigned short characs2[5] = {60, 20, 40, 50, 70};
        Duration duration2(3, 45);
        Song *song2 = new Song("Song Title 2", "Artist 2", characs2, duration2);

        // Calculate similarity for the songs
        double similarity1 = song1.calculateSimilarity();
        double similarity2 = song2->calculateSimilarity();

        // Print info for the first two songs
        std::cout << "Song 1 Info:" << std::endl;
        song1.printInfo();
        std::cout << "Similarity: " << similarity1 << std::endl;
        std::cout << std::endl;

        std::cout << "Song 2 Info:" << std::endl;
        song2->printInfo();
        std::cout << "Similarity: " << similarity2 << std::endl;
        std::cout << std::endl;

        // Calculate difference in duration between the two songs
        int durationDiffInSeconds = song1.calculateDurationDifferenceInSeconds(*song2);

        // Print difference in duration in seconds
        std::cout << "Difference in Duration Between Song 1 and Song 2:" << std::endl;
        std::cout << "Seconds: " << durationDiffInSeconds << std::endl;
        std::cout << std::endl;

        // Clean up heap-allocated memory
        delete song2;

        // Create an array that can store 100 songs
        Song songs[100];

        // Add the first two songs to the array
        songs[0] = song1;
        songs[1] = *song2;

        // Print info for the first two songs in the array
        std::cout << "Songs in the array:" << std::endl;
        songs[0].printInfo();
        songs[1].printInfo();

        // Create 98 songs using the default constructor
        for (int i = 2; i < 100; ++i) {
            songs[i] = Song();
        }

        // Print info for the last song in the array
        songs[99].printInfo();
    } catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
