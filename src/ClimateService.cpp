#include "ClimateService.h"
#include <iostream>

std::string ClimateService::getName() const {
    return "Climate Service";
}

void ClimateService::start() {
    std::cout << "[Climate] Climate Service Started." << std::endl;
}

void ClimateService::stop() {
    std::cout << "[Climate] Climate Service Stopped." << std::endl;
}