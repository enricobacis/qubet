#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent) :
    audioEnabled(true)
{
    //Inizialize the effectList
    Phonon::MediaObject *effect;
    QString path = ":/effects/resources/effects";
    QDir dir = QDir(path);
    QString dirString;
    for(uint i = 0; i < dir.count(); i++)
    {
        dirString = path + "/" + dir[i];
        effect = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(dirString));
        effectsList.append(effect);
    }
}

AudioManager::~AudioManager()
{
    disconnect(this);
}

void AudioManager::enableAudio(GLboolean enabled)
{
    if (audioEnabled && !enabled)
    {
        audioEnabled = false;
        pauseAmbientMusic();
    }
    if (!audioEnabled && enabled)
    {
        audioEnabled = true;
        continueAmbientMusic();
    }
}

void AudioManager::playAmbientMusic(QString filename)
{
    currentFileName = filename;
    mediaObject = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(currentFileName));
    connect (mediaObject, SIGNAL(aboutToFinish()), this, SLOT(enqueueMediaObject()));
    mediaObject->play();
}

void AudioManager::enqueueMediaObject()
{
    mediaObject->enqueue(currentFileName);
}

void AudioManager::pauseAmbientMusic()
{
    mediaObject->pause();
}

void AudioManager::continueAmbientMusic()
{
    mediaObject->play();
}

void AudioManager::playEffect(GLint effectId)
{
    effectsList.at(effectId)->play();
}

void AudioManager::run()
{

}
