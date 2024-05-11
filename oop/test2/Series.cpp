#include "Series.h"

Series::Series(const std::string& _seriesTitle) : LibraryItem("", 0, 0), title(_seriesTitle) {}

void Series::addVolume(Volume* volume) {
    if (volumes.size() >= 3) {
        throw std::invalid_argument("Cannot add more than 3 volumes to the series.");
    }
    volumes.push_back(volume);
}

void Series::display() const {
    std::cout << "Series Title: " << title << std::endl;
    std::cout << "Volumes:" << std::endl;
    for (const auto& volume : volumes) {
        volume->display();
        std::cout << std::endl;
    }
}

double Series::getPrice() const {
    double totalPrice = 0;
    for (const auto& volume : volumes) {
        totalPrice += volume->getPrice();
    }
    if (volumes.size() < 3) {
        return totalPrice * 0.8; 
    }
    return totalPrice;
}

double Series::getWorldbuildingQuality() const {
    double totalQuality = 0;
    for (const auto& volume : volumes) {
        totalQuality += volume->getWorldbuildingQuality();
    }
    return totalQuality / volumes.size();
}

std::ostream& operator<<(std::ostream& os, const Series& series) {
    os << "Series Title: " << series.title << std::endl;
    os << "Volumes:" << std::endl;
    for (const auto& volume : series.volumes) {
        volume->display();
        os << std::endl;
    }
    return os;
}

