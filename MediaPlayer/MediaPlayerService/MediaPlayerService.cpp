#include "MediaPlayerService.h"

const qint64 SEEK_VALUE = 5000;

MediaPlayerService::MediaPlayerService(QObject *parent)
    : QObject{parent}
    , _mediaPlayer(new QMediaPlayer(this))
    , _audioOutput(new QAudioOutput)
    , _videoWidget(new QVideoWidget)
{
    _mediaPlayer->setAudioOutput(_audioOutput);
    _mediaPlayer->setVideoOutput(_videoWidget);

    connect(_mediaPlayer, &QMediaPlayer::positionChanged, this, &MediaPlayerService::positionChanged);
    connect(_mediaPlayer, &QMediaPlayer::durationChanged, this, &MediaPlayerService::durationChanged);
    connect(_mediaPlayer, &QMediaPlayer::playbackStateChanged, this, &MediaPlayerService::playbackStateChanged);
    connect(_audioOutput, &QAudioOutput::mutedChanged, this, &MediaPlayerService::mutedChanged);
}

QVideoWidget *MediaPlayerService::getVideoWidget() const
{
    return _videoWidget;
}

void MediaPlayerService::play() const
{
    _mediaPlayer->play();
}

void MediaPlayerService::pause() const
{
    _mediaPlayer->pause();
}

void MediaPlayerService::seekForward() const
{
    _mediaPlayer->setPosition(getPosition() + SEEK_VALUE);
}

void MediaPlayerService::seekBackward() const
{
    _mediaPlayer->setPosition(std::max(0ll, getPosition() - SEEK_VALUE));
}

qint64 MediaPlayerService::getPosition() const
{
    return _mediaPlayer->position();
}

qint64 MediaPlayerService::getDuration() const
{
    return _mediaPlayer->duration();
}

QMediaPlayer::PlaybackState MediaPlayerService::playbackState() const
{
    return _mediaPlayer->playbackState();
}

bool MediaPlayerService::isMuted() const
{
    return _audioOutput->isMuted();
}

float MediaPlayerService::volume() const
{
    return _audioOutput->volume();
}

void MediaPlayerService::setMedia(const QUrl &source) const
{
    if (source.isValid())
    {
        _mediaPlayer->setSource(source);
    }
}

void MediaPlayerService::setPosition(qint64 position) const
{
    _mediaPlayer->setPosition(position);
}

void MediaPlayerService::setMuted(bool muted) const
{
    _audioOutput->setMuted(muted);
}

void MediaPlayerService::setVolume(float volume) const
{
    _audioOutput->setVolume(volume);
}
