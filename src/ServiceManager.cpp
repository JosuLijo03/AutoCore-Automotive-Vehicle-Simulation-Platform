#include "ServiceManager.h"
#include "Logger.h"
#include <iostream>

void ServiceManager::registerService(std::shared_ptr<IService> service) {
   services[service->getName()] = service;

Logger::info(service->getName() + " Registered");
}

void ServiceManager::startAllServices() {
    Logger::info("Starting all services...");

    for (auto &service : services) {
        service.second->start();
    }
}

void ServiceManager::stopAllServices() {
    Logger::info("Stopping all services...");

    for (auto &service : services) {
        service.second->stop();
    }
}

void ServiceManager::listServices() const {
   Logger::info("Registered Services:");

    for (const auto &service : services) {
        std::cout << "- " << service.first << std::endl;
    }
}