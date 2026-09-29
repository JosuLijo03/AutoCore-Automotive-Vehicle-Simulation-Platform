#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   
// Vehicle Information Panel


QFrame *vehicleFrame = new QFrame(ui->centralwidget);

vehicleFrame->setGeometry(
    5,
    2,
    330,
    310);
vehicleFrame->setStyleSheet(R"(

QFrame
{
    background-color: rgba(25,40,70,180);

    border: 2px solid #66CCFF;

    border-radius: 15px;
}

)");




vehicleFrame->lower();

   carImage = new HologramCar(ui->centralwidget);

QPixmap car(":/images/SUV transparent.png");

if (car.isNull())
{
    qDebug() << "Failed to load car image!";
}
else
{
    qDebug() << "Car loaded successfully.";
}

carImage->setPixmap(car);

carImage->setGeometry(
    30,
    355,
    400,
    210);
carImage->raise();
carImage->show();
    
    setStyleSheet(R"(
QMainWindow
{
    background-color: rgb(8,18,35);
}

QWidget#centralwidget
{
    background:transparent;
}

QLabel
{
    color:white;

    background:transparent;

    font-size:15px;

    font-weight:bold;
}

QPushButton
{


    color:white;

    border:2px solid #099dce;

    border-radius:12px;

    padding:8px;
}

QPushButton:hover
{
    background:#00AA44;
    color:white;
}

QPushButton:pressed
{
    background:#007733;
}

QDialog
{
    background-color: rgb(15,20,35);
}

QLabel
{
    color:white;
}

QComboBox
{
    background-color: rgb(30,45,70);
    color:white;
    border:2px solid #5DB8FF;
}

QPushButton
{
    background-color: rgb(30,45,70);
    color:white;
    border:2px solid #5DB8FF;
}

)");




    ui->locationButton->setEnabled(false);

    simulation = new SimulationEngine(&vehicle);

    statusAnalyzer = new VehicleStatusAnalyzer(&vehicle);

connect(&dashboardTimer,
        &QTimer::timeout,
        this,
        &MainWindow::updateDashboard);

dashboardTimer.start(1000);
    // Database
    database.connect(QString("vehicle.db"));
    database.createTables();

    // Services
    engine = ServiceFactory::createEngineService(&vehicle);
    door = ServiceFactory::createDoorService(&vehicle);
    battery = ServiceFactory::createBatteryService(&vehicle);
    climate = ServiceFactory::createClimateService();

    // Button Connections
    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onStartEngine);

    connect(ui->stopButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onStopEngine);

    connect(ui->lockButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onLockDoors);

    connect(ui->unlockButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onUnlockDoors);

    connect(ui->chargeButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onChargeBattery);

    connect(ui->historyButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onShowHistory);

    connect(ui->locationButton,
        &QPushButton::clicked,
        this,
        &MainWindow::onLocationTracker);

    connect(ui->exitButton,
            &QPushButton::clicked,
            this,
            &MainWindow::onExit);

    updateDashboard();
}

MainWindow::~MainWindow()
{
    dashboardTimer.stop();

    simulation->stopSimulation();

    delete simulation;

    delete statusAnalyzer;

    database.close();

    delete ui;
}

void MainWindow::onStartEngine()
{

        if (vehicle.isEngineRunning())
    {
        QMessageBox::information(
            this,
            "Vehicle",
            "Vehicle is already running.");

        return;
    }

    // Check if vehicle is ready
    if (!statusAnalyzer->isVehicleReady())
    {
        QMessageBox::warning(
            this,
            "Vehicle Not Ready",
            "Battery level is too low to start the vehicle.");

        return;
    }

    
    // Select Driving Mode


    QStringList modes;
    modes << "Manual Drive"
          << "Auto Drive";

    bool ok;

    QString selectedMode =
        QInputDialog::getItem(
            this,
            "Driving Mode",
            "Select Driving Mode:",
            modes,
            0,
            false,
            &ok);

    if (!ok)
        return;

    
    // Manual Drive
    

    if (selectedMode == "Manual Drive")
    {
        vehicle.setDrivingMode(DrivingMode::Manual);

        ui->drivingModeLabel->setText(
            "Driving Mode : Manual");

        // Disable Location Tracker
        ui->locationButton->setEnabled(false);
    }
    
    // Auto Drive
    
    else
    {
        vehicle.setDrivingMode(DrivingMode::AutoDrive);

        ui->drivingModeLabel->setText(
            "Driving Mode : Auto Drive");

        // Enable Location Tracker
        ui->locationButton->setEnabled(true);
    }

    
    // Start Vehicle
    

    engine->startEngine();

    simulation->startSimulation();

    database.logEvent(
        "Vehicle Started",
        selectedMode);

    updateDashboard();
}


void MainWindow::onStopEngine()
{

    if (!vehicle.isEngineRunning())
{
    QMessageBox::information(
        this,
        "Vehicle",
        "Vehicle is already stopped.");

    return;
}
    engine->stopEngine();

    simulation->stopSimulation();

vehicle.setDrivingMode(DrivingMode::Parked);

vehicle.setSpeed(0);

ui->locationButton->setEnabled(false);

    database.logEvent(
        "Engine Stopped",
        "Vehicle turned off");

    updateDashboard();
}

void MainWindow::onLockDoors()
{
    door->lockDoors();

    database.logEvent(
        "Doors Locked",
        "Driver locked the doors");

    updateDashboard();
}

void MainWindow::onUnlockDoors()
{
    door->unlockDoors();

    database.logEvent(
        "Doors Unlocked",
        "Driver unlocked the doors");

    updateDashboard();
}

void MainWindow::onChargeBattery()
{
    battery->charge(10);

    database.logEvent(
        "Battery Charged",
        "+10%");

    updateDashboard();
}

void MainWindow::onShowHistory()
{
    QString report =
        QString::fromStdString(
            statusAnalyzer->generateStatusReport());

    QMessageBox::information(
        this,
        "Current Vehicle Status",
        report);
}

void MainWindow::onLocationTracker()
{
    QMessageBox::information(
        this,
        "Location Tracker",

        "Auto Drive Activated\n\n"

        "GPS Module Initializing...\n"
        "Satellite Connection Established\n"
        "Vehicle Position Tracking Enabled\n\n"

        "Tracking Status : ACTIVE\n"
        "Navigation : Waiting for Destination\n\n"

        "No destination selected.");
}

void MainWindow::onExit()
{
    close();
}

void MainWindow::updateDashboard()
{
   
    if (vehicle.isEngineRunning())
     {
    ui->engineLabel->setText("Vehicle : READY");}

    else
{
    ui->engineLabel->setText("Vehicle : OFF");}


    // Doors
    if (vehicle.areDoorsLocked())
        ui->doorLabel->setText("Doors : Locked");
    else
        ui->doorLabel->setText("Doors : Unlocked");

    // Battery
    ui->batteryLabel->setText(
        QString("Battery : %1%").arg(vehicle.getBatteryLevel()));

    // Speed
    ui->speedLabel->setText(
        QString("Speed : %1 km/h").arg(vehicle.getSpeed()));

    
   
    ui->distanceLabel->setText(
        QString("Distance : %1 km")
            .arg(vehicle.getDistanceTravelled(), 0, 'f', 2));


switch(vehicle.getDrivingMode())
{
case DrivingMode::Parked:
    ui->drivingModeLabel->setText("Driving Mode : Parked");
    break;

case DrivingMode::Manual:
    ui->drivingModeLabel->setText("Driving Mode : Manual");
    break;

case DrivingMode::AutoDrive:
    ui->drivingModeLabel->setText("Driving Mode : Auto Drive");
    break;

case DrivingMode::Charging:
    ui->drivingModeLabel->setText("Driving Mode : Charging");
    break;

case DrivingMode::Service:
    ui->drivingModeLabel->setText("Driving Mode : Service");
    break;
}

ui->vehicleHealthLabel->setText(
    QString("Vehicle Health : %1")
        .arg(QString::fromStdString(
            statusAnalyzer->getOverallHealth())));



        }