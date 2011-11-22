//    Qubet  -  Copyright (C) 2011
//    Enrico Bacis
//    Daniele Ciriello

//    Qubet is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#include "window.h"
#include "defines.h"

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
