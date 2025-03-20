#include "homewindow.h"
#include "ui_homewindow.h"

#include "Utils/Factory.h"
#include "Database/RecentFile.h"
#include "UI/RecentFileWidget.h"
#include "MediaController/MediaController.h"

#include <QPointer>

HomeWindow::HomeWindow(const RecentFilesRepositoryPtr& filesRepository, MediaController* mediaController, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HomeWindow)
    , _filesRepository(filesRepository)
    , _mediaController(mediaController)
{
    ui->setupUi(this);

    initRecentFilesManager();
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::initRecentFilesManager() const
{
    Utils::Factory<RecentFileWidget*, const RecentFiles::RecentFile&, const QPointer<MediaController>&> factory =
        [](const RecentFiles::RecentFile& file, const QPointer<MediaController>& mediaController) {
            return new RecentFileWidget(file, mediaController);
        };

    ui->recentFilesManager->setFactory(factory);
    ui->recentFilesManager->setFilesRepository(_filesRepository);
    ui->recentFilesManager->setMediaController(QPointer<MediaController>(_mediaController));
    ui->recentFilesManager->loadRecentFiles();
}
