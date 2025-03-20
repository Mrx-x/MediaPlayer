#ifndef RECENTFILEWIDGET_H
#define RECENTFILEWIDGET_H

#include <QPushButton>
#include <QLabel>
#include <QPointer>

#include "RecentFile.h"
#include "MediaController.h"

class RecentFileWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit RecentFileWidget(const RecentFiles::RecentFile& file, const QPointer<MediaController>& mediaController, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    void InitUI();
    void UploadStyleSheet();

private:
    RecentFiles::RecentFile _file;
    QPointer<MediaController> _mediaController;
    QLabel* _fileNameLabel;
    QLabel* _icon;
};

#endif // RECENTFILEWIDGET_H
