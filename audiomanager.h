#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QThread>
#include <QDir>

#include <phonon/MediaObject>
#include <phonon/AudioOutput>

/**
 * @brief
 *
 * @version 1.0
 * @author \#34
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
    explicit AudioManager(QObject *_parent = 0);

    /**
     * @brief
     *
     */
    ~AudioManager();

private:
    QObject *parent;
    QString currentFileName; /**< TODO */
    bool audioEnabled; /**< TODO */
    Phonon::AudioOutput *audioOutput; /**< TODO */
    Phonon::MediaObject *ambientMusic; /**< TODO */
    QList<Phonon::MediaObject*> effectsList; /**< TODO */

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
    */
    void enqueueMediaObject();

    /**
     * @brief
     *
     * @param effectId
     */
    void playEffect(int effectId);

};

#endif // AUDIOMANAGER_H
