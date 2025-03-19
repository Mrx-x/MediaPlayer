#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStyle>
#include <QFileDialog>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QtMultimediaWidgets/QVideoWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MediaController;
class ContentSwitcher;
class HomeWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MediaController* mediaController, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_file_triggered();
    void on_playPauseButton_clicked();
    void on_backwardSeekButton_clicked();
    void on_forwardSeekButton_clicked();

    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);

    void timeLineSliderValueChanged(int value);
    void playbackStateChanged(QMediaPlayer::PlaybackState newState);

    void mutedChanged(bool muted);
    void setMuted();
    void volumeChanged(int value);

    void on_actionHome_triggered();

private:
    void initUI() const;
    void initContentSwitcher() const;
    void initPreviewWidget() const;
    void updateVolumeButtonIcon(const QString& name) const;
    void updateDurationLabels(qint64 duration) const;

    QTime millisecondsToTime(qint64 duration) const;

private:
    void switchContent(const QString& objName) const;

private:
    Ui::MainWindow* ui;
    HomeWindow* _homeWindow;
    ContentSwitcher* _contentSwitcher;
    MediaController* _mediaController;
    qint64 _totalDuration;
};
#endif // MAINWINDOW_H
