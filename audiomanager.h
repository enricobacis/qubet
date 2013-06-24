//    Qubet  -  Copyright (C) 2011
//    Enrico Bacis
//    Daniele Ciriello

//    Qubet is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QThread>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QMediaPlaylist>

/**
 * @brief It is a semi-thread class to manage the audio of Qubet.
 *        It can manage an ambientMusic and different effects.
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
     * @param _parent is a callback variable to the parent of AudioManager.
     */
    explicit AudioManager(QObject *_parent = 0);

    /**
     * @brief Safely stops and destroys the AudioManager (including the ambientMusic and
     *        all the effects in the effectsList.
     */
    ~AudioManager();

    /**
     * @brief Returns the state of the audio.
     *
     * @returns true if audio is enabled, else false.
     */
    bool isAudioEnabled();


private:

    QObject *parent; /**< It is a callback variable to the parent of AudioManager. */
    bool audioEnabled; /**< It is the variable that states if the audio is currently enabled or not. */
    QMediaPlayer *ambientMusic; /**< It is the QMediaPlayer of the current ambient music. */
    QMediaPlaylist *playlist; /**< It is the playlist to be played as ambient music. */
    QMap<QString,QSoundEffect*> effectsList; /**< It is the QMap of effects and their filename. */

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
     * @param enabled is the variable to states the AudioManager to enable or disable the audio.
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
