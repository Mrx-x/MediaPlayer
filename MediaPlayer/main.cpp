#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "MediaPlayerService.h"
#include "MediaController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
    w.show();
    return a.exec();
}
