#ifndef MEDIAPLAYERSERVICE_H
#define MEDIAPLAYERSERVICE_H

#include <QObject>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QAudioOutput>

class MediaPlayerService : public QObject
{
    Q_OBJECT
public:
    explicit MediaPlayerService(QObject *parent = nullptr);

public:
    QVideoWidget* getVideoWidget() const;

public:
    void play() const;
    void pause() const;
    void seekForward() const;
    void seekBackward() const;

public:
    qint64 getPosition() const;
    qint64 getDuration() const;
    QMediaPlayer::PlaybackState playbackState() const;
    bool isMuted() const;
    float volume() const;

public:
    void setMedia(const QUrl& source) const;
    void setPosition(qint64 position) const;
    void setMuted(bool muted) const;
    void setVolume(float volume) const;

signals:
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void playbackStateChanged(QMediaPlayer::PlaybackState newState);
    void mutedChanged(bool muted);

private:
    QMediaPlayer* _mediaPlayer;
    QAudioOutput* _audioOutput;
    QVideoWidget* _videoWidget;
};

#endif // MEDIAPLAYERSERVICE_H
