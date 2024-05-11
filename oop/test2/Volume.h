#ifndef VOLUME_H
#define VOLUME_H

#include <iostream>
#include <vector>
#include <string>
#include "LibraryItem.h"

class Volume : public LibraryItem {
private:
    unsigned int publicationYear;

public:
    Volume(const std::string& _title, double _price, double _worldbuildingQuality, unsigned int _publicationYear);
    void display() const override;
};

#endif