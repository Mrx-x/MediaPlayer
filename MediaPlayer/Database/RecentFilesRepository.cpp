#include "RecentFilesRepository.h"
#include "DatabaseManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

namespace RecentFiles
{
    void RecentFilesRepository::addRecentFile(const QString &filePath)
    {
        auto database = DatabaseManager::instance().getDatabase();
        if (!database.isOpen()) return;

        QSqlQuery query;
        QString queryFormat = "INSERT INTO RecentFiles (FilePath, LastPlayed) "
                              "VALUES('%1', CURRENT_TIMESTAMP) "
                              "ON CONFLICT(FilePath) DO UPDATE SET LastPlayed = CURRENT_TIMESTAMP;";

        QString queryText = queryFormat.arg(filePath);

        if (!query.exec(queryText))
        {
    #ifdef DEBUG_MODE
            qDebug() << query.lastError();
    #endif
        }
    }

    QList<RecentFile> RecentFilesRepository::getRecentFiles(int limit)
    {
        auto database = DatabaseManager::instance().getDatabase();
        QList<RecentFile> files;

        if (!database.isOpen()) return files;

        QSqlQuery query;
        QString queryFormat = "SELECT FilePath, LastPlayed FROM RecentFiles "
                              "ORDER BY LastPlayed DESC LIMIT '%1'";

        QString queryText = queryFormat.arg(limit);

        if (query.exec(queryText))
        {
            while (query.next())
            {
                QString path = query.value(0).toString();
                QDateTime lastPlayed = query.value(1).toDateTime();
                files.append(RecentFile(path, lastPlayed));
            }
        }
        else
        {
    #ifdef DEBUG_MODE
            qDebug() << query.lastError();
    #endif
        }

        return files;
    }

    void RecentFilesRepository::clearOldRecords(int maxRecords)
    {
        auto database = DatabaseManager::instance().getDatabase();
        if (!database.isOpen()) return;

        QSqlQuery query;
        QString queryFormat = "DELETE FROM RecentFiles WHERE id not IN ("
                              "SELECT id FROM RecentFiles ORDER BY LastPlayed DESC LIMIT '%1')";

        QString queryText = queryFormat.arg(maxRecords);

        if (!query.exec(queryText))
        {
    #ifdef DEBUG_MODE
            qDebug() << query.lastError();
    #endif
        }
    }
}
