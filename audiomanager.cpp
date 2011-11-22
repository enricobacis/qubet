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

AudioManager::AudioManager(QObject *_parent) :
    parent(_parent),
    currentFileName(""),
    audioEnabled(true),
    ambientMusic(NULL)
{
    //Inizialize the effectsList

    QString path = "resources/effects";
    QDir dir = QDir(path);
    Phonon::MediaObject *effect;

    for (uint i = 0; i < dir.count(); i++)
    {
        effect = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(path + "/" + dir[i]));
        connect(effect, SIGNAL(finished()), effect, SLOT(stop()));
        effectsList.insert(dir[i], effect);
    }
}

AudioManager::~AudioManager()
{
    if (ambientMusic != NULL)
    {
        ambientMusic->clear();
        ambientMusic->~MediaObject();
    }

    Phonon::MediaObject *effect;

    for (QMap<QString,Phonon::MediaObject*>::iterator i = effectsList.begin(); i != effectsList.end(); i++)
    {
        if (i.value() != NULL)
        {
            effect = dynamic_cast<Phonon::MediaObject*>(i.value());
            effect->clear();
            effect->~MediaObject();
        }
    }

    effectsList.~QMap();

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

        for (QMap<QString,Phonon::MediaObject*>::iterator i = effectsList.begin(); i != effectsList.end(); i++)
        {
            if (i.value() != NULL)
                dynamic_cast<Phonon::MediaObject*>(i.value())->stop();
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
    if (filename == currentFileName)
        return;

    currentFileName = filename;

    if (ambientMusic != NULL)
        ambientMusic->clear();

    ambientMusic = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(currentFileName));
    connect (ambientMusic, SIGNAL(aboutToFinish()), this, SLOT(enqueueMediaObject()));
    if(audioEnabled)
        ambientMusic->play();
}

void AudioManager::stopAmbientMusic()
{
    if (ambientMusic != NULL)
        ambientMusic->clear();
}

void AudioManager::enqueueMediaObject()
{
    ambientMusic->enqueue(currentFileName);
}

void AudioManager::playEffect(QString effectName)
{
    if(audioEnabled)
    {
        Phonon::MediaObject *effect = effectsList.value(effectName, NULL);

        if (effect != NULL)
        {
            if (effect->state() == Phonon::PlayingState)
                effect->seek(0);
            else
                effect->play();
        }
    }
}

void AudioManager::run()
{ }
