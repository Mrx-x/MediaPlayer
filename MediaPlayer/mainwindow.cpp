#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QResizeEvent>

#include "MediaController.h"
#include "MediaPlayerService.h"
#include "VolumeControlWidget.h"

MainWindow::MainWindow(MediaController* mediaController, QWidget *parent)
    : QMainWindow(parent)
    , _mediaController(mediaController)
    , ui(new Ui::MainWindow)
    , _totalDuration(0)
{
    ui->setupUi(this);

    initUI();
    volumeChanged(ui->volumeSlider->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI() const
{
    auto boxLayout = new QVBoxLayout();

    boxLayout->setContentsMargins(0, 0, 0, 0);
    boxLayout->addWidget(_mediaController->getMediaService()->getVideoWidget());

    ui->videoFrameContainer->setLayout(boxLayout);

    connect(_mediaController->getMediaService(), &MediaPlayerService::durationChanged, this, &MainWindow::durationChanged);
    connect(_mediaController->getMediaService(), &MediaPlayerService::positionChanged, this, &MainWindow::positionChanged);
    connect(_mediaController->getMediaService(), &MediaPlayerService::playbackStateChanged, this, &MainWindow::playbackStateChanged);
    connect(_mediaController->getMediaService(), &MediaPlayerService::mutedChanged, this, &MainWindow::mutedChanged);
    connect(ui->volumeControlWidget, &VolumeControlWidget::volumeChanged, this, &MainWindow::volumeChanged);
    connect(ui->volumeButton, &QPushButton::clicked, this, &MainWindow::setMuted);

    connect(ui->timeLineSlider, &QAbstractSlider::valueChanged, this, &MainWindow::timeLineSliderValueChanged);
}

void MainWindow::updateVolumeButtonIcon(const QString &name) const
{
    ui->volumeButton->setIcon(QIcon(":/icons/" + name + ".png"));
}

void MainWindow::updateDurationLabels(qint64 duration) const
{
    if (_totalDuration || duration)
    {
        const auto currentTime = millisecondsToTime(duration);
        const auto totalTime = millisecondsToTime(_totalDuration);

        QString format = "hh:mm:ss";

        ui->currentTimeLabel->setText(currentTime.toString(format));
        ui->totalTimeLabel->setText(totalTime.toString(format));
    }
}

QTime MainWindow::millisecondsToTime(qint64 duration) const
{
    QTime time(duration / (3600 * 1000), (duration / (60 * 1000)) % 60, (duration / 1000) % 60);
    return time;
}

void MainWindow::on_actionOpen_file_triggered()
{
    const auto fileName = QFileDialog::getOpenFileName(nullptr, tr("Select file"), "", tr("MP4 files (*.mp4)"));
    if (!fileName.isEmpty())
    {
        _mediaController->setMedia(QUrl(fileName));
        on_playPauseButton_clicked();
    }
}


void MainWindow::on_playPauseButton_clicked()
{
    _mediaController->togglePlayPouse();
}

void MainWindow::on_backwardSeekButton_clicked()
{
    _mediaController->seekBackward();
}

void MainWindow::on_forwardSeekButton_clicked()
{
    _mediaController->seekForward();
}

void MainWindow::durationChanged(qint64 duration)
{
    ui->timeLineSlider->setRange(0, duration);
    _totalDuration = duration;
}

void MainWindow::positionChanged(qint64 position)
{
    ui->timeLineSlider->setValue(position);
    updateDurationLabels(position);
}

void MainWindow::timeLineSliderValueChanged(int value)
{
    if (ui->timeLineSlider->isSliderDown())
    {
        _mediaController->setPosition(ui->timeLineSlider->value());
    }
}

void MainWindow::playbackStateChanged(QMediaPlayer::PlaybackState newState)
{
    switch (newState)
    {
    case QMediaPlayer::PlaybackState::PlayingState:
        ui->playPauseButton->setIcon(QIcon(":/icons/pause.png"));
        break;
    default:
        ui->playPauseButton->setIcon(QIcon(":/icons/play.png"));
        break;
    }
}

void MainWindow::mutedChanged(bool muted)
{
    if (muted) updateVolumeButtonIcon("mute");
    else volumeChanged(_mediaController->volume() * 100);
}

void MainWindow::setMuted()
{
    _mediaController->setMuted(!_mediaController->isMuted());
}

void MainWindow::volumeChanged(int value)
{
    _mediaController->setVolume(value / 100.0f);

    if (value == 0)
        updateVolumeButtonIcon("mute");
    else if (value < 50)
        updateVolumeButtonIcon("lowSound");
    else
        updateVolumeButtonIcon("sound");
}

