#include "Bookstore.h"
#include <iostream>

void Bookstore::addItem(LibraryItem* item) {
    items.push_back(item);
}

void Bookstore::displayItemsWithWorldBuildingQuality(double minWorldbuildingQuality) const {
    std::cout << "Items with worldbuilding quality greater than " << minWorldbuildingQuality << ":" << std::endl;
    for (const auto& item : items) {
        if (item->getWorldbuildingQuality() > minWorldbuildingQuality) {
            item->display();
            std::cout << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Bookstore& bookstore) {
    for (const auto& item : bookstore.items) {
        os << *item << std::endl;
    }
    return os;
}

