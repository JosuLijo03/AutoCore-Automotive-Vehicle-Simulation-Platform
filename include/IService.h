#ifndef ISERVICE_H
#define ISERVICE_H

#include <string>

class IService {
public:
    virtual ~IService() = default;

    virtual std::string getName() const = 0;

    virtual void start() = 0;

    virtual void stop() = 0;
};

#endif