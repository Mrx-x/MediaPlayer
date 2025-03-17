#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QStyleFactory>

#include "MediaPlayerService.h"
#include "MediaController.h"
#include "Config.h"

int main(int argc, char *argv[])
{
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication a(argc, argv);
    a.setApplicationName(APP_NAME);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MediaPlayer_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MediaPlayerService playerService;
    MediaController mediaController(&playerService);

    MainWindow w(&mediaController);
    w.setWindowTitle(APP_NAME);
    w.show();
    return a.exec();
}
