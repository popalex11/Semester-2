#ifndef DURATION_H
#define DURATION_H

class Duration {
private:
    int minutes;
    int seconds;

public:
    Duration();
    Duration(int m, int s);

    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }

    Duration operator-(const Duration& other) const;
};

#endif  // DURATION_H
