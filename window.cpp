#include "window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Qubet " + QString(QUBET_VERSION));

    qubetWidget = new Qubet(this);
    setCentralWidget(qubetWidget);

    move(STD_MOVE_X, STD_MOVE_Y);
    resize(STD_WIDTH, STD_HEIGHT);
}

Window::~Window()
{

}

void Window::closeEvent(QCloseEvent *event)
{
    qubetWidget->~Qubet();
    event->accept();
}
