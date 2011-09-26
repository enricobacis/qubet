#include "audiomanager.h"

AudioManager::AudioManager(QObject *parent)
{
    mediaObject = new Phonon::MediaObject(this);
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    //Phonon::Path path =
    Phonon::createPath(mediaObject, audioOutput);

    connect (mediaObject, SIGNAL(aboutToFinish()), this, SLOT(enqueueMediaObject()));
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
    mediaObject->setCurrentSource(Phonon::MediaSource(currentFileName));
    mediaObject->enqueue(currentFileName);
    mediaObject->enqueue(currentFileName);
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
