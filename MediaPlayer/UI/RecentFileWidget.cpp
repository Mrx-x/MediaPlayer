#include "RecentFileWidget.h"

#include <QUrl>
#include <QFile>
#include <QVBoxLayout>
#include <QPixmap>

#include "MediaController.h"

RecentFileWidget::RecentFileWidget(const RecentFiles::RecentFile& file, const QPointer<MediaController>& mediaController, QWidget* parent)
    : QPushButton{nullptr}
    , _file(file)
    , _mediaController(mediaController)
    , _fileNameLabel(new QLabel(this))
    , _icon(new QLabel(this))
{
    InitUI();
}

void RecentFileWidget::mousePressEvent(QMouseEvent* event)
{
    if (_mediaController)
    {
        _mediaController->setMedia(QUrl(_file.getFilePath()));
    }
    QPushButton::mousePressEvent(event);
}

void RecentFileWidget::InitUI()
{
    auto layout = new QVBoxLayout(this);

    setAttribute(Qt::WA_StyledBackground, true);
    setMinimumSize(120, 130);
    setMaximumSize(180, 190);

    _fileNameLabel->setObjectName("fileNameLabel");

    UploadStyleSheet();

    QUrl url(_file.getFilePath());
    if (url.isValid())
    {
        _fileNameLabel->setText(url.fileName());
    }

    _icon->setPixmap(QPixmap(":/icons/recentFile.png"));

    layout->addWidget(_icon);
    layout->addWidget(_fileNameLabel);
    setLayout(layout);
}

void RecentFileWidget::UploadStyleSheet()
{
    QFile style;
    style.setFileName(":/qss/RecentFileWidget.css");
    if (style.open(QFile::ReadOnly))
    {
        auto qssString = style.readAll();
        setStyleSheet(qssString);
    }
}
