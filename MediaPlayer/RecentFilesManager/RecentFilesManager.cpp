#include "RecentFilesManager.h"
#include "RecentFilesRepository.h"

#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QOperatingSystemVersion>

const int NUMBER_ITEMS_IN_ROW = 4;

RecentFilesManager::RecentFilesManager(QWidget* parent)
    : QWidget{parent}
    , _factory(nullptr)
    , _layout(new QGridLayout(this))
{
    setLayout(_layout);
}

void RecentFilesManager::loadRecentFiles()
{
    if (!_factory || _filesRepository.expired() || !_mediaController) return;

    const auto recentFiles = _filesRepository.lock()->getRecentFiles();
    int idx = 0;

    for (const auto& file : recentFiles)
    {
        if (!fileExists(QUrl(file.getFilePath()).path())) continue;

        auto widget = _factory.Create(file, _mediaController);
        _layout->addWidget(widget, idx / NUMBER_ITEMS_IN_ROW, idx % NUMBER_ITEMS_IN_ROW);
        ++idx;
    }
}

bool RecentFilesManager::fileExists(const QString& path) const
{
    QString filePath = path;

    filePath.replace('/', QDir::separator());
    filePath.replace('\\', QDir::separator());

    if ((QOperatingSystemVersion::current().currentType() == QOperatingSystemVersionBase::OSType::Windows) && filePath.startsWith(QDir::separator()))
    {
        filePath = filePath.mid(1);
    }

    QFileInfo check_file(filePath);
    return check_file.exists() && check_file.isFile();
}
