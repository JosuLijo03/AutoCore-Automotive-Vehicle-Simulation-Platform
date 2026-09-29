#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <memory>
#include <QLabel>

#include "VehicleState.h"
#include "EngineService.h"
#include "DoorService.h"
#include "BatteryService.h"
#include "ClimateService.h"
#include "ServiceFactory.h"
#include "DatabaseManager.h"
#include "SimulationEngine.h"
#include "VehicleStatusAnalyzer.h"
#include "HologramCar.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:

    // Vehicle Controls
    void onStartEngine();
    void onStopEngine();

    // Door Controls
    void onLockDoors();
    void onUnlockDoors();

    // Charging
    void onChargeBattery();

    // Vehicle Status
    void onShowHistory();

    // Location Tracker
    void onLocationTracker();

    // Exit
    void onExit();

    // Dashboard Refresh
    void updateDashboard();

private:

    // UI
    Ui::MainWindow *ui;
 

    HologramCar *carImage;

    //-----------------------------
    // Vehicle State
    //-----------------------------
    VehicleState vehicle;

    //-----------------------------
    // Services
    //-----------------------------
    std::shared_ptr<EngineService> engine;
    std::shared_ptr<DoorService> door;
    std::shared_ptr<BatteryService> battery;
    std::shared_ptr<ClimateService> climate;

    //-----------------------------
    // Database
    //-----------------------------
    DatabaseManager database;

    //-----------------------------
    // Simulation
    //-----------------------------
    SimulationEngine* simulation;

    //-----------------------------
    // Vehicle Status Analyzer
    //-----------------------------
    VehicleStatusAnalyzer* statusAnalyzer;

    //-----------------------------
    // Dashboard Timer
    //-----------------------------
    QTimer dashboardTimer;
};

#endif // MAINWINDOW_H