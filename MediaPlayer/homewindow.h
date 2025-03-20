#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QWidget>

namespace Ui { class HomeWindow; }

namespace RecentFiles { class RecentFilesRepository; }

class MediaController;

class HomeWindow : public QWidget
{
    Q_OBJECT

public:
    using RecentFilesRepositoryPtr = std::weak_ptr<RecentFiles::RecentFilesRepository>;

public:
    explicit HomeWindow(const RecentFilesRepositoryPtr& filesRepository, MediaController* mediaController, QWidget* parent = nullptr);
    ~HomeWindow();

public:
    void initRecentFilesManager() const;

private:
    Ui::HomeWindow *ui;
    RecentFilesRepositoryPtr _filesRepository;
    MediaController* _mediaController;
};

#endif // HOMEWINDOW_H
