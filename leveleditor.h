#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QKeyEvent>
#include <QMap>
#include <QtOpenGL>

#include "vector3f.h"
#include "level.h"
#include "cubestring.h"
#include "alphabet.h"
#include "actionlist.h"


/**
 * @brief
 *
 */
class LevelEditor : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief
     *
     * @param
     * @param _obstacleModelsList
     * @param _levelsList
     * @param parent
     */
    explicit LevelEditor(QMap<GLint,Vector3f*> &_obstacleModelsList, QMap<GLint,Level*> &_levelsList,QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, QObject *parent = 0);

    /**
     * @brief
     *
     */
    ~LevelEditor();

    /**
     * @brief Method to draw the levelEditor.
     *
     * @param simplifyForPicking [default = false] is used to draw a simplified scene
     *        used for the picking function.
     */
    void draw(GLboolean simplifyForPicking = false);

    /**
     * @brief launch the signal playAmbientMusic.
     */
    GLvoid playAudio();

private:

    QObject *parent;  /**<  It is a callback variable to the parent of the widget. */
    QMap<GLint,Level*> levelsList; /**< TODO */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< TODO */
    QMap<GLint,GLuint> iconsList;  /**< It is the iconsList provided by Qubet object. */
    GLboolean audioEnabled;  /**< It is the state of the audio. */
    GLboolean isMoving; /**< It is the variable that states if the menu is moving or not. */
    Level *level; /**< TODO */
    GLint state; /**< TODO */
    GLint currentView;  /**< It is the value of the current view */
    Vector3f *cameraPosition; /**< TODO */
    GLuint lenght; /**< TODO */
    GLuint currentLenght; /**< TODO */
    GLuint width; /**< TODO */
    GLuint currentWidth; /**< TODO */
    Alphabet *alphabet; /**< It is the alphabet provided by Qubet. */
    ActionList *currentActions; /**< It is the list of the current menu steps. */
    Vector3f *cameraOffset; /**< It is the camera offset for the editor. */
    Skin *volumeSkin; /**< It is the skin of the volume button */
    GLfloat angleRotVolumeCube;  /**< It is the current rotation angle of the volume icon. */
    CubeString *lenghtDisplay; /**< It is the lenght CubeString. */
    CubeString *widthDisplay; /**< It is the width CubeString. */
    /**
     * @brief
     *
     */
    void quitEditor();

    /**
     * @brief
     *
    */
    GLvoid lenghten();

    /**
     * @brief
     *
    */
    GLvoid shorten();

    /**
     * @brief
     *
    */
    GLvoid enlarge();

    /**
     * @brief
     *
    */
    GLvoid reduce();


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
     */
    void levelEditorClosed();

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

#endif // LEVELEDITOR_H
