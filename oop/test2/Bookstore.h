#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include "LibraryItem.h"
#include <vector>

class Bookstore {
private:
    std::vector<LibraryItem*> items;
public:
    void addItem(LibraryItem* item);
    void displayItemsWithWorldBuildingQuality(double minQuality) const;

    friend std::ostream& operator<<(std::ostream& os, const Bookstore& bookstore);

};

#endif