#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent)
{
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
    qDebug()<<"the ambient music should start";
}

void AudioManager::enqueueMediaObject()
{
    mediaObject->enqueue(currentFileName);
    qDebug()<<"the ambient music should restart soon";
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

}

void AudioManager::run()
{

}
