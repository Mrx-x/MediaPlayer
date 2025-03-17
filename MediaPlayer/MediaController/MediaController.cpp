#include "MediaController.h"
#include "MediaPlayerService.h"

MediaController::MediaController(MediaPlayerService* playerService, QObject *parent)
    : QObject{parent}
    , _playerService(playerService)
{
}

MediaPlayerService *MediaController::getMediaService() const
{
    return _playerService;
}

void MediaController::togglePlayPouse() const
{
    if (isPause())
    {
        _playerService->play();
    }
    else
    {
        _playerService->pause();
    }
}

void MediaController::seekForward() const
{
    _playerService->seekForward();
}

void MediaController::seekBackward() const
{
    _playerService->seekBackward();
}

bool MediaController::isPause() const
{
    switch(_playerService->playbackState())
    {
    case QMediaPlayer::PlaybackState::PlayingState:
    {
        return false;
    }
    case QMediaPlayer::PlaybackState::PausedState: case QMediaPlayer::PlaybackState::StoppedState:
    {
        return true;
    }
    }
    return true;
}

bool MediaController::isMuted() const
{
    return _playerService->isMuted();
}

float MediaController::volume() const
{
    return _playerService->volume();
}

void MediaController::setPosition(qint64 position) const
{
    _playerService->setPosition(position);
}

void MediaController::setMedia(const QUrl &source) const
{
    _playerService->setMedia(source);
}

void MediaController::setMedia(QUrl &&source) const
{
    _playerService->setMedia(std::move(source));
}

void MediaController::setMuted(bool muted) const
{
    _playerService->setMuted(muted);
}

void MediaController::setVolume(float volume) const
{
    _playerService->setVolume(volume);
}
