#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QThread>
#include <QKeyEvent>
#include "vector3f.h"
#include "level.h"

#include <GL/gl.h>

class LevelEditor : public QThread
{
    Q_OBJECT

public:
    explicit LevelEditor(QMap<Vector3f, GLint> &_obstacleModelsList, QMap<QString, GLint> &_levelsList, QObject *parent = 0);
    ~LevelEditor();

    void start();

private:
    QMap<QString, GLint> levelsList;
    QMap <Vector3f*, GLint> obstacleModelsList;
    Level *level;
    GLint state;
    Vector3f *cameraPosition;

    void quitEditor();
    void draw();
    void run();

private slots:
    void keyPressed(QKeyEvent *e);
    void itemClicked(GLint id);

signals:
    void levelEditorClosed();
    void enableAudio(bool enabled);
    void playAmbientMusic(QString filename);
    void playEffect(GLint effectId);

};

#endif // LEVELEDITOR_H
