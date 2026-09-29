#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <unordered_map>
#include <memory>
#include <string>

#include "IService.h"

class ServiceManager {
private:
    std::unordered_map<std::string, std::shared_ptr<IService>> services;

public:
    void registerService(std::shared_ptr<IService> service);

    void startAllServices();

    void stopAllServices();

    void listServices() const;
};

#endif