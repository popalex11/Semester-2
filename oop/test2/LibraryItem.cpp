#include "LibraryItem.h"

LibraryItem::LibraryItem(const std::string& _title, double _price, double _worldbuildingQuality) :
    title(_title), price(_price), worldbuildingQuality(_worldbuildingQuality) {}


double LibraryItem::getPrice() const {
    return price;
}

void LibraryItem::setPrice(double _price) {
    price = _price;
}

double LibraryItem::getWorldbuildingQuality() const {
    return worldbuildingQuality;
}

void LibraryItem::setWorldbuildingQuality(double _worldbuildingQuality) {
    if (_worldbuildingQuality < 1 || _worldbuildingQuality > 5) {
        throw std::invalid_argument("Worldbuilding quality must be between 1 and 5.");
    }
    worldbuildingQuality = _worldbuildingQuality;
}

std::ostream& operator<<(std::ostream& os, const LibraryItem& item) {
    os << "Title: " << item.title << ", Price: " << item.price << ", Worldbuilding Quality: " << item.worldbuildingQuality;
    return os;
}