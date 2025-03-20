#ifndef RECENTFILESMANAGER_H
#define RECENTFILESMANAGER_H

#include <QWidget>
#include <QGridLayout>
#include <QPointer>

#include "Factory.h"
#include "RecentFileWidget.h"

namespace RecentFiles { class RecentFilesRepository; class RecentFile; }

class MediaController;

class RecentFilesManager : public QWidget
{
    Q_OBJECT
public:
    using Factory = Utils::Factory<RecentFileWidget*, const RecentFiles::RecentFile&, const QPointer<MediaController>&>;
    using RecentFilesRepositoryPtr = std::weak_ptr<RecentFiles::RecentFilesRepository>;

public:
    explicit RecentFilesManager(QWidget *parent = nullptr);

public:
    void setFactory(const Factory& factory) { _factory = factory; }
    void setFilesRepository(const RecentFilesRepositoryPtr& filesRepository) { _filesRepository = filesRepository; }
    void setMediaController(const QPointer<MediaController> mediaController) { _mediaController = mediaController; }

public:
    void loadRecentFiles();

private:
    bool fileExists(const QString& path) const;

private:
    Factory _factory;
    RecentFilesRepositoryPtr _filesRepository;
    QPointer<MediaController> _mediaController;
    QGridLayout* _layout;
};

#endif // RECENTFILESMANAGER_H
