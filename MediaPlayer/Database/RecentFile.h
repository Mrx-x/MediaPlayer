#ifndef RECENTFILE_H
#define RECENTFILE_H

#include <QString>
#include <QDateTime>

namespace RecentFiles
{
    class RecentFile
    {
    public:
        RecentFile() = default;
        RecentFile(const QString& path, const QDateTime& lastPlayed);
        RecentFile(QString&& path, QDateTime&& lastPlayed);
        RecentFile(const RecentFile& other);

        RecentFile& operator=(const RecentFile& other);
        RecentFile& operator=(RecentFile&& other) noexcept;

        ~RecentFile() = default;

    public:
        QString getFilePath() const { return _filePath; }
        QDateTime getLastPlayed() const { return _lastPlayed; }

    private:
        QString _filePath;
        QDateTime _lastPlayed;
    };
}
#endif // RECENTFILE_H
