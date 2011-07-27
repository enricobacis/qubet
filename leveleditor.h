#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QThread>
#include <QKeyEvent>
#include "vector3f.h"
#include "level.h"

#include <GL/gl.h>

/**
 * @brief
 *
 */
class LevelEditor : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param
     * @param _obstacleModelsList
     * @param QMap<QString
     * @param _levelsList
     * @param parent
     */
    explicit LevelEditor(QMap<Vector3f*, GLint> &_obstacleModelsList, QMap<QString, GLint> &_levelsList, QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~LevelEditor();

private:
    QMap<QString, GLint> levelsList; /**< TODO */
    QMap <Vector3f*, GLint> obstacleModelsList; /**< TODO */
    Level *level; /**< TODO */
    GLint state; /**< TODO */
    Vector3f *cameraPosition; /**< TODO */

    /**
     * @brief
     *
     */
    void quitEditor();
    /**
     * @brief
     *
     */
    void draw();

    /**
     * @brief
     *
     */
    void run();

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
