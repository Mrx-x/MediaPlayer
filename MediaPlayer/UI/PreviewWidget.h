#ifndef PREVIEWWIDGET_H
#define PREVIEWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixMap>
#include <QPointer>
#include <QVideoWidget>

#include "ContentSwitcher.h"

class PreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreviewWidget(QWidget *parent = nullptr);

public:
    void mousePressEvent(QMouseEvent *event) override;

public:
    void setVideoWidget(QVideoWidget* widget);
    void setContentSwitcher(ContentSwitcher* contentSwitcher);

public slots:
    void sourceChanged(const QUrl &media);
    void contentSwitched(const QString& objName);

private:
    void setFrameVisible(bool visible) const;

private:
    QLabel* _sourceName;
    QHBoxLayout* _layout;
    QPointer<QVideoWidget> _pVideoWidget;
    QPointer<ContentSwitcher> _pContentSwitcher;
};

#endif // PREVIEWWIDGET_H
