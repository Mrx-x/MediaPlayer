#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

namespace RecentFiles
{
    class DatabaseManager
    {
    public:
        static DatabaseManager& instance();
        QSqlDatabase getDatabase();

    public:
        DatabaseManager(const DatabaseManager&) = delete;
        DatabaseManager& operator=(const DatabaseManager&) = delete;

    private:
        DatabaseManager();
        ~DatabaseManager();

        void createTables();

    private:
        QSqlDatabase _database;
    };
}
#endif // DATABASEMANAGER_H
