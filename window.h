#ifndef MAINQUBET_H
#define MAINQUBET_H

#include <QMainWindow>

#include "qubet.h"
#include "defines.h"

/**
 * @brief
 *
 */
class Window : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit Window(QWidget *parent = 0);

    /**
     * @brief
     *
     */
    ~Window();


private:
    Qubet *qubetWidget; /**< TODO */

    /**
     * @brief
     *
     * @param event
     */
    void closeEvent(QCloseEvent *event);

};

#endif // MAINQUBET_H
