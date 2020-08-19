#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("DHT22 & QT Creator");
    w.setFixedSize(411,120);
    w.show();
    return a.exec();
}
