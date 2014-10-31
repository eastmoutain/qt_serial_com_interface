#include "terminal.h"
#include <QCoreApplication>
#include <QApplication>
#include <QRegExp>
#include <QtSerialPort/QSerialPort>
#include <QObject>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextStream standardOutput(stdout);
    QSerialPort serial_port;

    terminal w(&serial_port);

    w.show();

    return a.exec();
}

