#ifndef VOLUMECONTROLWIDGET_H
#define VOLUMECONTROLWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QSlider>
#include <QGraphicsOpacityEffect>

class VolumeControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VolumeControlWidget(QWidget *parent = nullptr);

protected:
    void showEvent(QShowEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void initUI();
    void showSlider();
    void hideSlider();

signals:
    void volumeChanged(int value);

private:
    QGraphicsOpacityEffect* _graphicsEffect;
    QPropertyAnimation* _animation;
    QPushButton* _volumeButton;
    QSlider* _volumeSlider;
    bool _initialized;
};

#endif // VOLUMECONTROLWIDGET_H
