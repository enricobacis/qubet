#include <QtGui/QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Qubet");

    Window w;
    w.setWindowIcon(QIcon("resources/qubet.png"));
    w.show();

    return app.exec();
}
