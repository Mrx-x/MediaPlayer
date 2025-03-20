#include "Listener.h"
#include "RecentFilesRepository.h"

#include <QUrl>

namespace RecentFiles
{
    Listener::Listener(const RecentFilesRepositoryPtr& filesRepository, QObject* parent)
        : QObject{parent}
        , _filesRepository(filesRepository)
    {

    }

    void Listener::sourceChanged(const QUrl& media)
    {
        if (media.isValid() && !_filesRepository.expired())
        {
            _filesRepository.lock()->addRecentFile(media.toString());
        }
    }
}
