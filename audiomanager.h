#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QThread>
#include <QSound>

#include <GL/gl.h>

class AudioManager : public QThread
{
    Q_OBJECT

public:
    explicit AudioManager(QObject *parent = 0);
    ~AudioManager();

private:
    QSound *ambientMusic;
    bool audioEnabled;

    void run();

private slots:
    void enableAudio(bool enabled);
    void playAmbientMusic(QString filename);
    void pauseAmbientMusic();
    void continueAmbientMusic();
    void playEffect(GLint effectId);

};

#endif // AUDIOMANAGER_H
