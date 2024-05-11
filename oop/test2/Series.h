#ifndef SERIES_H
#define SERIES_H


#include <vector>
#include "Volume.h"
#include "LibraryItem.h"

class Series : public LibraryItem {
private:
    std::string title;
    std::vector<Volume*> volumes;

public:
    Series(const std::string& _seriesTitle);

    void addVolume(Volume* volume);

    void display() const override;

    double getPrice() const override;

    double getWorldbuildingQuality() const override;

    friend std::ostream& operator<<(std::ostream& os, const Series& series);

};

#endif 