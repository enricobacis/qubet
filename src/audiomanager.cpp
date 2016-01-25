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


#include "audiomanager.h"
#include <QDir>
#include <QMediaPlaylist>

AudioManager::AudioManager(QObject *_parent) :
    parent(_parent),
    audioEnabled(true),
    ambientMusic(NULL)
{
    //Inizialize the effectsList

    QDir dir = QDir("resources/effects");
    QSoundEffect *effect;

    for (uint i = 0; i < dir.count(); i++)
    {
        if (!dir[i].startsWith('.'))
        {
            effect = new QSoundEffect();
            effect->setSource(QUrl::fromLocalFile(dir.absoluteFilePath(dir[i])));
            effectsList.insert(dir[i], effect);
        }
    }

    ambientMusic = new QMediaPlayer();

    playlist = new QMediaPlaylist();
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
}

AudioManager::~AudioManager()
{
    ambientMusic->stop();
    ambientMusic->~QMediaPlayer();

    playlist->~QMediaPlaylist();

    QSoundEffect *effect;

    for (QMap<QString,QSoundEffect*>::iterator i = effectsList.begin(); i != effectsList.end(); ++i)
    {
        if (i.value() != NULL)
        {
            effect = dynamic_cast<QSoundEffect*>(i.value());
            effect->stop();
            effect->~QSoundEffect();
        }
    }

    this->disconnect(parent);
    parent->disconnect(this);
}

bool AudioManager::isAudioEnabled()
{
    return audioEnabled;
}

void AudioManager::enableAudio(bool enabled)
{
    if (audioEnabled && !enabled)
    {
        audioEnabled = false;
        ambientMusic->pause();

        for (QMap<QString,QSoundEffect*>::iterator i = effectsList.begin(); i != effectsList.end(); ++i)
        {
            if (i.value() != NULL)
                dynamic_cast<QSoundEffect*>(i.value())->stop();
        }
    }
    else if (!audioEnabled && enabled)
    {
        audioEnabled = true;
        ambientMusic->play();
    }
}

void AudioManager::playAmbientMusic(QString filename)
{
    QDir dir = QDir("resources/music");

    ambientMusic->stop();
    playlist->clear();
    playlist->addMedia(QUrl::fromLocalFile(dir.absoluteFilePath(filename)));
    ambientMusic->setPlaylist(playlist);

    if(audioEnabled)
        ambientMusic->play();
}

void AudioManager::stopAmbientMusic()
{
    ambientMusic->stop();
}

void AudioManager::playEffect(QString effectName)
{
    if(audioEnabled)
    {
        QSoundEffect *effect = effectsList.value(effectName, NULL);

        if (effect != NULL)
        {
            effect->stop();
            effect->play();
        }
    }
}

void AudioManager::run()
{ }
