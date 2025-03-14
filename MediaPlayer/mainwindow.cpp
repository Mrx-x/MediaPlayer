#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MediaControlPanel.h"
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (ui->mediaControlPanel)
    {
        auto newSize = event->size();
        auto oldSize = event->oldSize();
        if (!oldSize.isValid()) return;
        auto sz = newSize - oldSize;

        auto mediaControlPanelGeometry = ui->mediaControlPanel->geometry();
        mediaControlPanelGeometry.setX(event->size().width() / 2 - mediaControlPanelGeometry.width() / 2);
        mediaControlPanelGeometry.setY(mediaControlPanelGeometry.y() + sz.height());

        ui->mediaControlPanel->setGeometry(mediaControlPanelGeometry);
    }
}
