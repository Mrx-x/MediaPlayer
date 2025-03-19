#include "DatabaseManager.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace RecentFiles
{
    DatabaseManager &DatabaseManager::instance()
    {
        static DatabaseManager instance;
        return instance;
    }

    QSqlDatabase DatabaseManager::getDatabase()
    {
        return _database;
    }

    DatabaseManager::DatabaseManager()
    {
        _database = QSqlDatabase::addDatabase("QSQLITE");
        _database.setDatabaseName("RecentFiles");

        if (!_database.open())
        {
    #ifdef DEBUG_MODE
            qDebug() << _database.lastError();
    #endif
        }
        else
        {
            createTables();
        }
    }

    DatabaseManager::~DatabaseManager()
    {
        if (_database.isOpen()) _database.close();
    }

    void DatabaseManager::createTables()
    {
        QSqlQuery query;
        QString createTable = "CREATE TABLE IF NOT EXISTS RecentFiles ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "FilePath TEXT UNIQUE, "
                              "LastPlayed DATETIME DEFAULT CURRENT_TIMESTAMP);";

        if (!query.exec(createTable))
        {
    #ifdef DEBUG_MODE
            qDebug() << query.lastError();
    #endif
        }
    }
}
