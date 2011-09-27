#ifndef MENU_H
#define MENU_H

#include <QtOpenGL>
#include <QImage>
#include <QKeyEvent>
#include <QMap>
#include <QList>
#include <QDebug>

#include "menu_defines.h"
#include "defines.h"

#include "skin.h"
#include "utilities.h"
#include "actionlist.h"
#include "cubestring.h"
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
     * @param _alphabet is the reference to Qubet's alphabet.
     * @param _parent is a callback variable to the parent of the parent.
     */
    explicit Menu(QMap<GLint,Skin*> &_skinsList, QMap<GLint,QString> &_levelsList, Alphabet *_alphabet, QObject *_parent);

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

    /**
     * @brief launch the signal playAmbientMusic.
     */
    GLvoid playAudio();


private:

    QObject *parent;  /**<  It is a callback variable to the parent of the widget. */
    GLint currentSkin; /**< It is the id of the current choosen skin. */
    QMap<GLint,Skin*> skinsList; /**< It is the skinsList provided by Qubet object. */
    QMap<GLint,QString> levelsList; /**< It is the levelsList provided by Qubet object. */
    Alphabet *alphabet; /**< It is the alphabet provided by Qubet. */
    GLint itemSelected; /**< It is the id of the current menu action selected. */
    GLboolean isMoving; /**< It is the variable that states if the menu is moving or not. */
    Vector3f *cameraOffset; /**< It is the camera offset for the menu. */
    ActionList *currentActions; /**< It is the list of the current menu steps. */
    GLint gameType; /**< It is the selected gameType. */
    GLfloat angleRotCube;  /**< It is the current rotation angle of the cube. */
    GLfloat spinCube;  /**< It is the spin step of the skin selection cube. */
    GLfloat angleRotVolumeCube;  /**< It is the current rotation angle of the volume icon. */
    GLboolean audioEnabled;  /**< It is the state of the audio. */
    Skin *volumeSkin; /**< It is the skin of the volume button */

    CubeString *storyButton; /**< It is the storyButton CubeString. */
    CubeString *arcadeButton; /**< It is the arcadeButton CubeString. */
    CubeString *editorButton; /**< It is the editorButton CubeString. */
    CubeString *skinName;  /**< It is the skinName CubeString. */


    /**
     * @brief Change the current skin and select the previous one.
     */
    GLvoid previousSkin();

    /**
     * @brief Change the current skin and select the next one.
     */
    GLvoid nextSkin();


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
