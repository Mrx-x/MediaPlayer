#include "RecentFile.h"

namespace RecentFiles
{
    RecentFile::RecentFile(const QString& path, const QDateTime& lastPlayed)
        : _filePath(path)
        , _lastPlayed(lastPlayed)
    {

    }

    RecentFile::RecentFile(QString&& path, QDateTime&& lastPlayed)
        : _filePath(std::move(path))
        , _lastPlayed(std::move(lastPlayed))
    {

    }

    RecentFile::RecentFile(const RecentFile& other)
        : _filePath(other._filePath)
        , _lastPlayed(other._lastPlayed)
    {

    }

    RecentFile& RecentFile::operator=(const RecentFile& other)
    {
        return *this = RecentFile(other);
    }

    RecentFile& RecentFile::operator=(RecentFile&& other) noexcept
    {
        std::swap(_filePath, other._filePath);
        std::swap(_lastPlayed, other._lastPlayed);

        return *this;
    }
}
