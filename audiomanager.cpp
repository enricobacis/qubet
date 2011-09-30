#include "audiomanager.h"

AudioManager::AudioManager(QObject *_parent) :
    parent(_parent),
    audioEnabled(true)
{
    //Inizialize the effectList
    Phonon::MediaObject *effect;

    QString path = ":/effects/resources/effects";
    QDir dir = QDir(path);
    QString dirString;

    for (uint i = 0; i < dir.count(); i++)
    {
        dirString = path + "/" + dir[i];
        effect = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(dirString));
        effectsList.append(effect);
    }
}

AudioManager::~AudioManager()
{
    this->disconnect(parent);
    parent->disconnect(this);
}

void AudioManager::enableAudio(GLboolean enabled)
{
    if (audioEnabled && !enabled)
    {
        audioEnabled = false;
        mediaObject->pause();
    }
    else if (!audioEnabled && enabled)
    {
        audioEnabled = true;
        mediaObject->play();
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

void AudioManager::playEffect(GLint effectId)
{
    if(audioEnabled)
        effectsList.at(effectId)->play();
}

void AudioManager::run()
{
}
