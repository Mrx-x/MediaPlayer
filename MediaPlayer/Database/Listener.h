#ifndef LISTENER_H
#define LISTENER_H

#include <QObject>

namespace RecentFiles
{
    class RecentFilesRepository;

    class Listener : public QObject
    {
        Q_OBJECT
    public:
        using RecentFilesRepositoryPtr = std::weak_ptr<RecentFilesRepository>;
        explicit Listener(const RecentFilesRepositoryPtr& filesRepository, QObject *parent = nullptr);

    public slots:
        void sourceChanged(const QUrl &media);

    private:
        RecentFilesRepositoryPtr _filesRepository;
    };
}
#endif // LISTENER_H
