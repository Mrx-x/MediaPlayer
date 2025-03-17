#include "VolumeControlWidget.h"

#include <QPointer>

const int ANIMATION_DURATION = 300;

VolumeControlWidget::VolumeControlWidget(QWidget *parent)
    : QWidget{parent}
    , _graphicsEffect(new QGraphicsOpacityEffect(this))
    , _animation(new QPropertyAnimation(_graphicsEffect, "opacity"))
    , _volumeButton(nullptr)
    , _volumeSlider(nullptr)
    , _initialized(false)
{
    _animation->setDuration(ANIMATION_DURATION);
}

void VolumeControlWidget::showEvent(QShowEvent *event)
{
    if (!_initialized)
    {
        initUI();
    }
    QWidget::showEvent(event);
}

void VolumeControlWidget::enterEvent(QEnterEvent *event)
{
    showSlider();
    QWidget::enterEvent(event);
}

void VolumeControlWidget::leaveEvent(QEvent *event)
{
    hideSlider();
    QWidget::leaveEvent(event);
}

void VolumeControlWidget::initUI()
{
    _volumeButton = findChild<QPushButton*>("volumeButton");
    _volumeSlider = findChild<QSlider*>("volumeSlider");

    if (!_volumeButton || !_volumeSlider)
    {
        qWarning() << "[VolumeControlWidget] - Child elements could not be found";
        return;
    }

    _volumeSlider->setGraphicsEffect(_graphicsEffect);
    _volumeSlider->hide();

    connect(_volumeSlider, &QSlider::valueChanged, this, &VolumeControlWidget::volumeChanged);
    _initialized = true;
}

void VolumeControlWidget::showSlider()
{
    if (!_volumeSlider) return;

    _volumeSlider->show();

    _animation->setDuration(ANIMATION_DURATION);
    _animation->setStartValue(0.0);
    _animation->setEndValue(1.0);
    _animation->start();
}

void VolumeControlWidget::hideSlider()
{
    if (!_volumeSlider) return;

    _animation->setDuration(ANIMATION_DURATION);
    _animation->setStartValue(1.0);
    _animation->setEndValue(0.0);
    _animation->start();

    connect(_animation, &QPropertyAnimation::finished, this, [self=QPointer<VolumeControlWidget>(this)]() {
        if (self && self->_graphicsEffect->opacity() == 0.0)
        {
            self->_volumeSlider->hide();
        }
    });
}
