#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "level.h"
#include "cubestringlist.h"
#include "actionlist.h"

/**
 * @brief
 *
 * @version 1.0
 * @author \#34
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
    explicit LevelEditor(QMap<GLint,Vector3f*> &_obstacleModelsList, QMap<GLint,Level*> &_levelsList, QMap<GLint,GLuint> &_iconsList, Alphabet *_alphabet, QObject *parent = 0);

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
    CubeString *labelLenght;  /**< It is the labelLenght CubeString.*/
    CubeString *labelWidth;  /**< It is the labelWidth CubeString. */
    CubeString *create; /**< It is the create button CubeString. */
    CubeString *setLevelNameLabel;  /**< It is the setLevelName CubeString. */
    CubeString *next;  /**< It is the next button CubeString. */
    CubeStringList *setLevelNameForm;  /**< It is the setLevelNameForm cubeStringList  */

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
     * @brief This signal is emitted to set the Qubet's Mouse Move Tracking sensibility.
     *        The modes are:
     *          0 - no signal emitted.
     *          1 - the signal mouseMoved is emitted only when the mouse is moved
     *              and one of the mouse buttons are clicked.
     *          2 - the signal mouseMoved is emitted always when the mouse is
     *              moved.
     *
     * @param mode It is the selected mode.
     */
    void setMouseMovementTracking(int mode);

    /**
     * @brief Signal emitted to enable or disable the audio.
     *
     * @param enabled is the variable that states if the audio is to enable or not.
     */
    void enableAudio(bool enabled);

    /**
     * @brief Signal emitted to play the ambient music.
     *
     * @param filename is the filename to play.
     */
    void playAmbientMusic(QString filename);

    /**
     * @brief Signal emitted to stop the current ambient music.
     */
    void stopAmbientMusic();

    /**
     * @brief Signal emitted to play an effect.
     *
     * @param effectName is the name of the effect to play.
     */
    void playEffect(QString effectName);

};

#endif // LEVELEDITOR_H
