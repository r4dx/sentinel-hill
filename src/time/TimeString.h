#ifndef TIMESTRING_H
#define TIMESTRING_H

#include <string>
#include <ctime>

class ITimeProvider {
public:
    virtual std::string now() const = 0;
};

class MillisTimeProvider : public ITimeProvider {
public:
    std::string now() const;
    
private:
    std::time_t getUnixTime() const;
};

#endif /* TIMESTRING_H */

