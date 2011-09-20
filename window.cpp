#include "window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Qubet " + QString(QUBET_VERSION));

    qubetWidget = new Qubet(this);
    setCentralWidget(qubetWidget);

    move(MOVE_X, MOVE_Y);
    resize(WIDTH, HEIGHT);
}

Window::~Window()
{
}

void Window::closeEvent(QCloseEvent *event)
{
    qubetWidget->~Qubet();
    event->accept();
}
