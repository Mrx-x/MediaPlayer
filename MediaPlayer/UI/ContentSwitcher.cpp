#include "ContentSwitcher.h"
#include <QWidget>

ContentSwitcher::ContentSwitcher(QObject *parent)
    : QObject{parent}
{

}

void ContentSwitcher::addPlaceHolder(QBoxLayout *layout)
{
    if (_layout != layout) _layout = layout;
}

void ContentSwitcher::add(QWidget *widget)
{
    _container[widget->objectName()] = QPointer(widget);
    _layout->addWidget(widget);
}

void ContentSwitcher::removeWidget(const QString &objName)
{
    if (!objName.isEmpty() && _layout)
    {
        if (auto widget = _container.find(objName); widget != _container.end())
        {
            _layout->removeWidget(*widget);
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
    _container.clear();
}

void ContentSwitcher::switchContent(const QString &objName)
{
    if (objName.isEmpty()) return;
    if (auto widget = _container.find(objName); widget != _container.end())
    {
        switchContent(*widget);
    }
}

void ContentSwitcher::switchContent(QWidget *widget)
{
    if (_layout)
    {
        for (int idx = 0; idx < _layout->count(); ++idx)
        {
            auto layoutItem = _layout->takeAt(idx);
            layoutItem->widget()->hide();
        }
    }
    widget->show();
}
