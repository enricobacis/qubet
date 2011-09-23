#ifndef MENU_H
#define MENU_H

#include <QtOpenGL>
#include <QGLWidget> //remove after
#include <QImage>
#include <QKeyEvent>
#include <QMap>
#include <QList>
#include <QDebug>

#include "menu_defines.h"
#include "defines.h"

#include "skin.h"
#include "utilities.h"
#include "vector3f.h"


/**
 * @brief Menu class used to show and manage the game menu.
 *
 * @version 1.0
 * @author \#34
 */
class Menu : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Create a Menu object used to show and manage the game menu.
     *
     * @post You have to connect parent's signals to this object's slots.
     *       For Qubet check the connectInputEvents function.
     *
     * @param _skinsList is the reference to Qubet's skinsList.
     * @param _levelsList is the reference to Qubet's levelsList.
     * @param _parent is a callback variable to the parent of the widget.
     */
    explicit Menu(QMap<GLint,Skin*> &_skinsList, QMap<GLint,QString> &_levelsList, QObject *_parent);

    /**
     * @brief Disconnect and Destroy a Menu object.
     */
    ~Menu();

    /**
     * @brief Method to draw the menu.
     *
     * @param simplifyForPicking [default = false] is used to draw a simplified scene
     *        used for the picking function.
     */
    GLvoid draw(GLboolean simplifyForPicking = false);


private:

    QObject *parent;  /**<  It is a callback variable to the parent of the widget. */
    GLint currentSkin; /**< It is the id of the current choosen skin */
    QMap<GLint,Skin*> skinsList; /**< skinsList provided by Qubet object. */
    QMap<GLint,QString> levelsList; /**< levelsList provided by Qubet object. */
    GLint itemSelected; /**< It is the id of the current menu action selected. */
    GLboolean isMoving; /**< It is the variable that state if the menu is moving or not. */
    Vector3f *cameraOffset; /**< It is the camera offset for the menu. */
    GLint currentStep; /**< It is the current menu step. */
    GLint gameType; /**< It is the selected gameType. */
    GLfloat angleRotCube;  /**< It is the current rotation angle of the cube. */
    GLfloat spinCube;  /**< It is the spin step of the skin selection cube. */
    GLboolean audioEnabled;  /**< It is the state of the audio. */
    QVector<QVector<GLint> > buttonsLettersAngles; /**< It is the list that contains the current buttons' rotation angles. */

    /**
     * @brief
     *
     */
    void previousSkin();

    /**
     * @brief
     *
     */
    void nextSkin();

    /**
     * @brief Check if the letter is moving yet, set currentStep if not
     *
     * @param Name is the Name of the object pointed by the cursor
    */
    GLvoid CheckLetterRotation(GLuint Name);

private slots:

    /**
     * @brief Slot called when the user clicks on a item.
     *
     * @param listNames is the QList<GLuint> of item's names.
     */
    void itemClicked(QList<GLuint> listNames);

    /**
     * @brief Slot called when the user releases the mouse button.
     *
     * @param event is the QMouseEvent*.
     */
    void mouseReleased(QMouseEvent *event);

    /**
     * @brief Slot called when the user moves the mouse.
     *
     * @param event is the QMouseEvent*.
     * @param listNames is the QList<GLuint> of item's names.
     */
    void mouseMoved(QMouseEvent *event, QList<GLuint> listNames);

    /**
     * @brief Slot called when the user presses a key on the keyboard.
     *
     * @param event is the QKeyEvent*.
     */
    void keyPressed(QKeyEvent *event);


signals:
    /**
     * @brief
     *
     * @param skinId
     */
    void playStory(GLint skinId);

    /**
     * @brief
     *
     * @param skinId
     * @param levelFilename
     */
    void playArcade(GLint skinId, QString levelFilename);

    /**
     * @brief
     *
     */
    void showLevelEditor();

    /**
     * @brief
     *
     * @param enabled
     */
    void enableAudio(GLboolean enabled);

    /**
     * @brief
     *
     * @param filename
     */
    void playAmbientMusic(QString filename);

    /**
     * @brief
     *
     * @param effectId
     */
    void playEffect(GLint effectId);

};

#endif // MENU_H
