#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QThread>
#include <QSound>

#include <GL/gl.h>

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
    QSound *ambientMusic; /**< TODO */
    bool audioEnabled; /**< TODO */

    /**
     * @brief
     *
     */
    void run();

private slots:
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
