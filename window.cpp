#include "window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Qubet " + QString(QUBET_VERSION));
    move(100, 100);
    resize(600, 400);

    qubetWidget = new Qubet(this);
    setCentralWidget(qubetWidget);
}

Window::~Window()
{

}

void Window::closeEvent(QCloseEvent *event)
{
    qubetWidget->~Qubet();
    event->accept();
}
