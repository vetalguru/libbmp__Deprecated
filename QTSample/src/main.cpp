#include "mainwindow.h"
#include <QApplication>

const int MAJOR_VERSION = 0;
const int MINOR_VERSION = 1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("QtSample");
    a.setApplicationVersion(QString("%1.%2").arg(MAJOR_VERSION).arg(MINOR_VERSION));
    MainWindow w;
    QString title = a.applicationName() + " (version " + a.applicationVersion() + ")";
    w.setWindowTitle(title);
    w.show();

    return a.exec();
}
