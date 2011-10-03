#ifndef POSITIONCONTROLLER_H
#define POSITIONCONTROLLER_H

#include "cube.h"

/**
 * @brief La classe PositionController controlla se il Cubo collide con degli ostacoli.
 *
 * @version 1.0
 * @author \#34
 */
class PositionController : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief Costruttore di oggetti di tipo PositionController.
     *
     * @param _cube Puntatore all'oggetto Cube
     * @param _level Puntatore all'oggetto Level
     * @param _parent Puntatore all'oggetto parent
     */
    explicit PositionController(Cube *_cube, Level *_level, QObject *_parent = 0);

    /**
     * @brief Distruttore di oggetti di tipo PositionController.
     *
     */
    ~PositionController();

private:
    Cube *cube; /**< Puntatore all'oggetto Cube */
    Level *level; /**< Puntatore all'oggetto Level */
    QTimer checkPositionTimer; /**< QTimer che regola ogni quanto viene lanciata la funzione checkCollision() che controlla le collisioni */

    /**
     * @brief Controlla se il cubo ha colliso con un ostacolo.
     *
     */
    GLvoid checkCollision();

    /**
     * @brief Reimplementazione della funzione run() della classe QThread.
     *
     *
     */
    void run();

signals:
    /**
     * @brief Segnale emesso quando il cubo collide con un ostacolo.
     *
     */
    void collision();

};

#endif // POSITIONCONTROLLER_H
