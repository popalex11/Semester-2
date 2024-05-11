#include <iostream>
#include "LibraryItem.h"
#include "Volume.h"
#include "Series.h"
#include "Bookstore.h"

int main() {
    Volume volume1("Volume 1", 10.99, 4.5, 2022);
    Volume volume2("Volume 2", 12.99, 4.2, 2023);
    Volume volume3("Volume 3", 14.99, 4.7, 2024);

    Series series("Adventure Series");
    series.addVolume(&volume1);
    series.addVolume(&volume2);

    Bookstore bookstore;
    bookstore.addItem(&volume1);
    bookstore.addItem(&volume2);
    bookstore.addItem(&volume3);
    bookstore.addItem(&series);

    std::cout << "Items with worldbuilding quality greater than 4.0:" << std::endl;
    bookstore.displayItemsWithWorldBuildingQuality(4.0);

    std::cout << "\nAll items in the bookstore:" << std::endl;
    std::cout << bookstore << std::endl;

    return 0;
}


//g++ -o App main.cpp Series.cpp Volume.cpp LibraryItem.cpp Bookstore.cpp 
// this to build the program and then ./App in terminal