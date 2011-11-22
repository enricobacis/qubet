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


#ifndef MAINQUBET_H
#define MAINQUBET_H

#include <QMainWindow>

#include "qubet.h"

/**
 * @brief This class is the QMainWindow, it is used to contain Qubet widget.
 *
 * @version 1.0
 * @author \#34
 */
class Window : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Create the QMainWindow.
     *
     * @param parent is a callback variable to the parent of the window.
     */
    explicit Window(QWidget *parent = 0);

    /**
     * @brief Destroy the QMainWindow (for what it worths).
     */
    ~Window();


private:
    Qubet *qubetWidget; /**< This variable refers to the Qubet instance. */

    /**
     * @brief This function is invoked when the user closes the Window.
     *        It is used to perform cleaning operations.
     *
     * @param event is the QCloseEvent*.
     */
    void closeEvent(QCloseEvent *event);

};

#endif // MAINQUBET_H
