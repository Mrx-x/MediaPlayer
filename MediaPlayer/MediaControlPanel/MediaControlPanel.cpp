#include "MediaControlPanel.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QMouseEvent>

static constexpr int ANIMATION_INTERVAL = 3000;
static constexpr int ANIMATION_DURATION = 300;
static constexpr int BOTTOM_OFFSET = 5;

MediaControlPanel::MediaControlPanel(QWidget *parent)
    : QFrame(parent)
    , _animation(nullptr)
    , _inactivityTimer(nullptr)
    , _isHidden(false)
{

    _animation = new QPropertyAnimation(this, "geometry");
    _animation->setDuration(ANIMATION_DURATION);
    _animation->setEasingCurve(QEasingCurve::OutBack);

    _inactivityTimer = new QTimer(this);
    _inactivityTimer->setInterval(ANIMATION_INTERVAL);
    _inactivityTimer->setSingleShot(true);
    connect(_inactivityTimer, &QTimer::timeout, this, &MediaControlPanel::hidePanel);

    qApp->installEventFilter(this);
}
MediaControlPanel::~MediaControlPanel()
{
    qApp->removeEventFilter(this);
}

bool MediaControlPanel::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        int mouseY = mouseEvent->globalPosition().y();

        if (mouseY >= parentWidget()->height() - height())
        {
            showPanel();
        }

        _inactivityTimer->start();
    }
    return QWidget::eventFilter(watched, event);
}

void MediaControlPanel::showPanel()
{
    if (_isHidden)
    {
        _animation->stop();
        _animation->setStartValue(geometry());
        _animation->setEndValue(QRect(x(), parentWidget()->height() - height() - BOTTOM_OFFSET, width(), height()));
        _animation->start();
        _isHidden = false;
    }
}

void MediaControlPanel::hidePanel()
{
    if (!_isHidden)
    {
        _animation->stop();
        _animation->setStartValue(geometry());
        _animation->setEndValue(QRect(x(), parentWidget()->height(), width(), height()));
        _animation->start();
        _isHidden = true;
    }
}
