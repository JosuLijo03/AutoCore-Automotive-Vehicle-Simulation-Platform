#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DatabaseManager
{
private:
    QSqlDatabase db;

public:
    DatabaseManager();
    ~DatabaseManager();

    bool connect(const QString& databaseName);

    void close();

     //Create all required tables
    bool createTables();

    // Event Logging
    bool logEvent(const QString& event,
                  const QString& details);

    // Display Events
    void showEventHistory();
};

#endif