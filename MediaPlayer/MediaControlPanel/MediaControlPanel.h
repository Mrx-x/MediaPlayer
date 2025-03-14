#ifndef MEDIACONTROLPANEL_H
#define MEDIACONTROLPANEL_H

#include <QPropertyAnimation>
#include <QTimer>
#include <QFrame>

class MediaControlPanel : public QFrame
{
    Q_OBJECT

public:
    MediaControlPanel(QWidget *parent = nullptr);
    ~MediaControlPanel();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void showPanel();
    void hidePanel();

private:
    QPropertyAnimation *_animation;
    QTimer *_inactivityTimer;
    bool _isHidden;
};



#endif // MEDIACONTROLPANEL_H
