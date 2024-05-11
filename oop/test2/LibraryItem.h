#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>
#include <iostream>


class LibraryItem {
protected:
    std::string title;
    double price;
    double worldbuildingQuality;

public:
    LibraryItem(const std::string& _title, double _price, double _worldbuildingQuality);
    
    virtual ~LibraryItem() {}

    virtual double getPrice() const;

    void setPrice(double _price);

    virtual double getWorldbuildingQuality() const;

    void setWorldbuildingQuality(double _worldbuildingQuality);

    virtual void display() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const LibraryItem& item);


};

std::ostream& operator<<(std::ostream& os, const LibraryItem& item);


#endif