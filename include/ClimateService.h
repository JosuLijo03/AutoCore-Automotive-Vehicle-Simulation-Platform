#ifndef CLIMATESERVICE_H
#define CLIMATESERVICE_H

#include "IService.h"

class ClimateService : public IService {
public:
    std::string getName() const override;

    void start() override;

    void stop() override;
};

#endif