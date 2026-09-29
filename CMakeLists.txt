cmake_minimum_required(VERSION 3.16)

project(AutoCore)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------- Qt ----------------
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql)

# ---------------- Include Directories ----------------
include_directories(
    include
    gui
)

# ---------------- Executable ----------------
add_executable(AutoCore

    # GUI
    gui/gui_main.cpp
    gui/mainwindow.cpp
    gui/mainwindow.h
    gui/mainwindow.ui

    gui/HologramCar.cpp
    gui/HologramCar.h

    # Backend Headers
    include/VehicleState.h
    include/EngineService.h
    include/DoorService.h
    include/BatteryService.h
    include/ClimateService.h
    include/ServiceFactory.h
    include/DatabaseManager.h
    include/SimulationEngine.h
    include/VehicleStatusAnalyzer.h

    # Qt resources
    resources.qrc

    # Backend
    src/Logger.cpp
    src/ServiceManager.cpp
    src/EngineService.cpp
    src/DoorService.cpp
    src/BatteryService.cpp
    src/ClimateService.cpp
    src/VehicleState.cpp
    src/HealthAnalyzer.cpp
    src/FaultManager.cpp
    src/Dashboard.cpp
    src/SensorManager.cpp
    src/VehicleController.cpp
    src/ServiceFactory.cpp
    src/DatabaseManager.cpp
    src/SimulationEngine.cpp
    src/VehicleStatusAnalyzer.cpp
)

# ---------------- Libraries ----------------
target_link_libraries(AutoCore
    PRIVATE
        Qt6::Widgets
        Qt6::Sql
)