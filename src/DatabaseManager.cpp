#include "DatabaseManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#include <iostream>
#include <iomanip>

DatabaseManager::DatabaseManager()
{
}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::connect(const QString& databaseName)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);

    if(!db.open())
    {
        std::cout << "Database connection failed.\n";
        return false;
    }

    std::cout << "Database connected successfully.\n";
    return true;
}

void DatabaseManager::close()
{
    if(db.isOpen())
        db.close();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;

    return query.exec(R"(

        CREATE TABLE IF NOT EXISTS vehicle_events
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,

            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,

            event TEXT NOT NULL,

            details TEXT
        );

    )");
}

bool DatabaseManager::logEvent(const QString& event,
                               const QString& details)
{
    QSqlQuery query;

    query.prepare(R"(

        INSERT INTO vehicle_events
        (event, details)

        VALUES
        (:event, :details)

    )");

    query.bindValue(":event", event);
    query.bindValue(":details", details);

    if(!query.exec())
    {
        std::cout << "Failed to log event.\n";
        return false;
    }

    return true;
}

void DatabaseManager::showEventHistory()
{
    QSqlQuery query;

    query.exec(R"(

        SELECT
            id,
            timestamp,
            event,
            details

        FROM vehicle_events

        ORDER BY id DESC;

    )");

    std::cout << "\n=============================================================\n";
    std::cout << "                VEHICLE EVENT HISTORY\n";
    std::cout << "=============================================================\n\n";

    std::cout
        << std::left
        << std::setw(5)  << "ID"
        << std::setw(22) << "Timestamp"
        << std::setw(22) << "Event"
        << "Details\n";

    std::cout << "--------------------------------------------------------------------------\n";

    while(query.next())
    {
        std::cout
            << std::left
            << std::setw(5)
            << query.value(0).toInt()

            << std::setw(22)
            << query.value(1).toString().toStdString()

            << std::setw(22)
            << query.value(2).toString().toStdString()

            << query.value(3).toString().toStdString()

            << std::endl;
    }
}