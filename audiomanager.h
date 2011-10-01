#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QThread>

#include <phonon/MediaObject>

/**
 * @brief It is a semi-thread class to manage the audio of Qubet.
 *        It can manage an ambientMusic and different effects using the Phonon framework.
 *
 *        It provides slots to connect the entity that are able to request an ambientMusic
 *        change, an effect to play or to enable and disable the music.
 *
 * @version 1.0
 * @author \#34
 */
class AudioManager : public QThread
{
    Q_OBJECT

public:

    /**
     * @brief Creates a new AudioManager loading all the effects in the folder resources/effects.
     *
     * @param parent is a callback variable to the parent of AudioManager.
     */
    explicit AudioManager(QObject *_parent = 0);

    /**
     * @brief Safely stops and destroys the AudioManager (including the ambientMusic and
     *        all the effects in the effectsList.
     */
    ~AudioManager();

private:
    QObject *parent; /**< It is a callback variable to the parent of AudioManager. */
    QString currentFileName; /**< It is the current ambientMusic filename. */
    bool audioEnabled; /**< It is the variable that states if the audio is currently enabled or not. */
    Phonon::MediaObject *ambientMusic; /**< It is the Phonon::MediaObject of the current ambient music. */
    QMap<QString,Phonon::MediaObject*> effectsList; /**< It is the QMap of effects and their filename. */

    /**
     * @brief It is the reimplementation of QThread's run() method. It is empty because
     *        the AudioManager is a semi-thread, all actions are managed by signals.
     */
    void run();


private slots:
    /**
     * @brief Sets the variable audioEnabled and pause or continue the ambientMusic.
     *        If enabled is false and there are currently playing effects they will be stopped.
     *
     * @param enabled is the variable to tell the AudioManager to enable or disable the audio.
     */
    void enableAudio(bool enabled);

    /**
     * @brief Plays the music file provided as parameter filename as ambientMusic.
     *
     *        It will also stop the current ambientMusic but not the effects.
     *
     * @param filename is the filename of the ambientMusic to play.
     */
    void playAmbientMusic(QString filename);

    /**
     * @brief Stops the current ambient music.
     */
    void stopAmbientMusic();

    /**
     * @brief It is a slot used privately to permit the loop of the ambientMusic with Phonon.
    */
    void enqueueMediaObject();

    /**
     * @brief Plays the effect that has got the parameter effectName filename.
     *
     *        For example if you have the file resources/effects/gameover.wav, in order
     *        to play this effect you have to call playEffect("gameover.wav").
     *
     *        If the effect is already playing it will be restarted.
     *
     * @param effectName is the effect's filename.
     */
    void playEffect(QString effectName);

};

#endif // AUDIOMANAGER_H
