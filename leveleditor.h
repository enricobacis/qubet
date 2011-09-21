#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QKeyEvent>
#include <QMap>
#include <QtOpenGL>

#include "vector3f.h"
#include "level.h"
#include "leveleditor_defines.h"


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
    explicit LevelEditor(QMap<GLint,Vector3f*> &_obstacleModelsList, QMap<GLint,QString> &_levelsList, QObject *parent = 0);

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

private:
    QMap<GLint,QString> levelsList; /**< TODO */
    QMap<GLint,Vector3f*> obstacleModelsList; /**< TODO */
    Level *level; /**< TODO */
    GLint state; /**< TODO */
    Vector3f *cameraPosition; /**< TODO */

    /**
     * @brief
     *
     */
    void quitEditor();

private slots:
    /**
     * @brief
     *
     * @param e
     */
    void keyPressed(QKeyEvent *e);

    /**
     * @brief
     *
     * @param id
     */
    void itemClicked(GLint id);

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
    void enableAudio(bool enabled);

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
