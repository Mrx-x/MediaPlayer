#ifndef MEDIACONTROLLER_H
#define MEDIACONTROLLER_H

#include <QObject>

class MediaPlayerService;

class MediaController : public QObject
{
    Q_OBJECT
public:
    explicit MediaController(MediaPlayerService* playerService, QObject *parent = nullptr);

public:
    MediaPlayerService* getMediaService() const;

public:
    void setPosition(qint64 position) const;
    void setMedia(const QUrl& source) const;
    void setMedia(QUrl&& source) const;
    void setMuted(bool muted) const;
    void setVolume(float volume) const;

public:
    void togglePlayPouse() const;
    void seekForward() const;
    void seekBackward() const;

public:
    bool isPause() const;
    bool isMuted() const;
    float volume() const;

signals:
    void positionChanged(qint64 position);
private:
    MediaPlayerService* _playerService;
};

#endif // MEDIACONTROLLER_H
