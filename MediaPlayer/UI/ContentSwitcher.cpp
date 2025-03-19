#include "ContentSwitcher.h"
#include <QWidget>

ContentSwitcher::ContentSwitcher(QObject *parent)
    : QObject{parent}
{
    _currentContent = _container.end();
}

void ContentSwitcher::addPlaceHolder(QBoxLayout *layout)
{
    if (_layout != layout) _layout = layout;
}

void ContentSwitcher::add(QWidget *widget)
{
    _container[widget->objectName()] = QPointer(widget);
    switchContent(widget);
}

void ContentSwitcher::removeWidget(const QString &objName)
{
    if (!objName.isEmpty() && _layout)
    {
        if (auto widget = _container.find(objName); widget != _container.end())
        {
            if (_currentContent == widget) _currentContent = _container.end();
            _layout->removeWidget(*widget);
            _container.remove(objName);
        }
    }
}

void ContentSwitcher::clear()
{
    if (_layout)
    {
        for (int idx = 0; idx < _layout->count(); ++idx)
        {
            auto layoutItem = _layout->takeAt(idx);
            _layout->removeItem(layoutItem);
        }
    }
}

void ContentSwitcher::switchContent(const QString &objName)
{
    if (objName.isEmpty()) return;
    if (_currentContent != _container.end() && _currentContent.key() == objName) return;
    if (auto widget = _container.find(objName); widget != _container.end())
    {
        _currentContent = widget;
        switchContent(*widget);
    }
}

void ContentSwitcher::switchContent(QWidget *widget)
{
    clear();
    widget->show();
    _layout->addWidget(widget);
    emit contentSwitched(widget->objectName());
}
