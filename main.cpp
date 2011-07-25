#include <QtGui/QApplication>
#include "mainqubet.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainQubet w;
    w.show();

    return a.exec();
}
