#include <QtGui/QApplication>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_INIT_RESOURCE(resources);

    Window w;
    w.show();

    return app.exec();
}
