#include "RecentFilesManager.h"
#include "RecentFilesRepository.h"

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
        auto widget = _factory.Create(file, _mediaController);
        _layout->addWidget(widget, idx / NUMBER_ITEMS_IN_ROW, idx % NUMBER_ITEMS_IN_ROW);
        ++idx;
    }
}
