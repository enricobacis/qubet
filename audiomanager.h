#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QThread>
//#include <QSound>
#include <QtOpenGL>
//#include <QDebug>

#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>


/**
 * @brief
 *
 */
class AudioManager : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit AudioManager(QObject *parent = 0);

    /**
     * @brief
     *
     */
    ~AudioManager();

private:
    QString currentFileName;
    QSound *ambientMusic; /**< TODO */
    bool audioEnabled; /**< TODO */
    Phonon::MediaObject *mediaObject; /**< TODO */
    QList<Phonon::MediaObject*> effectsList; /**< TODO */
    Phonon::AudioOutput *audioOutput; /**< TODO */

    /**
     * @brief
     *
     */
    void run();

private slots:
    /**
     * @brief Set audioEnabled and pause or continue the ambientMusic
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
    */
    void enqueueMediaObject();

    /**
     * @brief
     *
     */
    void pauseAmbientMusic();

    /**
     * @brief
     *
     */
    void continueAmbientMusic();

    /**
     * @brief
     *
     * @param effectId
     */
    void playEffect(GLint effectId);

};

#endif // AUDIOMANAGER_H
