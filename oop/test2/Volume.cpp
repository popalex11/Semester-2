
#include "Volume.h"

Volume::Volume(const std::string& title, double price, double worldbuildingQuality, unsigned int publicationYear)
    : LibraryItem(title, price, worldbuildingQuality), publicationYear(publicationYear) {}

void Volume::display() const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Price: " << price << std::endl;
    std::cout << "Worldbuilding Quality: " << worldbuildingQuality << std::endl;
    std::cout << "Publication Year: " << publicationYear << std::endl;
}
