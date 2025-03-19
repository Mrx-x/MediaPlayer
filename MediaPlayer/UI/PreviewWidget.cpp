#include "PreviewWidget.h"
#include <QMouseEvent>

PreviewWidget::PreviewWidget(QWidget *parent)
    : QWidget{parent}
    , _sourceName(new QLabel(this))
    , _layout(new QHBoxLayout())
    , _pVideoWidget(nullptr)
    , _pContentSwitcher(nullptr)
{
    setAttribute(Qt::WA_StyledBackground, true);

    _layout->addWidget(_sourceName);

    setLayout(_layout);
}

void PreviewWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (_pContentSwitcher && _pVideoWidget) _pContentSwitcher->switchContent(_pVideoWidget->objectName());
    }
    QWidget::mousePressEvent(event);
}

void PreviewWidget::setVideoWidget(QVideoWidget *widget)
{
    _pVideoWidget = widget;
}

void PreviewWidget::setContentSwitcher(ContentSwitcher *contentSwitcher)
{
    _pContentSwitcher = contentSwitcher;
}

void PreviewWidget::sourceChanged(const QUrl &media)
{
    if (media.isValid())
    {
        _sourceName->setText(media.fileName());
    }
}

void PreviewWidget::contentSwitched(const QString &objName)
{
    if (!objName.isEmpty() && _pVideoWidget)
    {
        if (objName != _pVideoWidget->objectName())
        {

            _layout->insertWidget(0, _pVideoWidget);
        }
    }
}
