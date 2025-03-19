#ifndef CONTENTSWITCHER_H
#define CONTENTSWITCHER_H

#include <QObject>
#include <QMap>
#include <QBoxLayout>
#include <QPointer>

class ContentSwitcher : public QObject
{
    Q_OBJECT
public:
    explicit ContentSwitcher(QObject *parent = nullptr);

public:
    void addPlaceHolder(QBoxLayout* layout);
    void add(QWidget* widget);
public:
    void removeWidget(const QString& objName);
    void clear();

public:
    void switchContent(const QString& objName);

private:
    void switchContent(QWidget* widget);

signals:
    void contentSwitched(const QString& objName);

private:
    QMap<QString, QPointer<QWidget>> _container;
    QMap<QString, QPointer<QWidget>>::Iterator _currentContent;
    QBoxLayout* _layout;
};

#endif // CONTENTSWITCHER_H
