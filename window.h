#ifndef MAINQUBET_H
#define MAINQUBET_H

#include <QMainWindow>
#include <QDebug>

#include "qubet.h"
#include "defines.h"


/**
 * @brief This class is the QMainWindow, it is used to contain Qubet widget.
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
     * @brief This function is called when the user closes the Window.
     *        It is used to perform cleaning operations.
     *
     * @param event is the QCloseEvent*.
     */
    void closeEvent(QCloseEvent *event);

};

#endif // MAINQUBET_H
