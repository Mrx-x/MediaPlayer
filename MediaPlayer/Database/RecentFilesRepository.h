#ifndef RECENTFILESREPOSITORY_H
#define RECENTFILESREPOSITORY_H

#include <QString>
#include <QList>

#include "RecentFile.h"

namespace RecentFiles
{
    class RecentFilesRepository
    {
    public:
        RecentFilesRepository() = default;
        ~RecentFilesRepository() = default;

    public:
        void addRecentFile(const QString& filePath);
        QList<RecentFile> getRecentFiles(int limit = 10);
        void clearOldRecords(int maxRecords = 10);
    };
}
#endif // RECENTFILESREPOSITORY_H
