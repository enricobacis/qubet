#include "audiomanager.h"

AudioManager::AudioManager(QObject *_parent) :
    parent(_parent),
    audioEnabled(true)
{
    //Inizialize the effectList
    Phonon::MediaObject *effect;

    QString path = "resources/effects";
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

void AudioManager::enableAudio(bool enabled)
{
    if (audioEnabled && !enabled)
    {
        audioEnabled = false;
        ambientMusic->pause();
    }
    else if (!audioEnabled && enabled)
    {
        audioEnabled = true;
        ambientMusic->play();
    }
}

void AudioManager::playAmbientMusic(QString filename)
{
    currentFileName = filename;
    ambientMusic = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource(currentFileName));
    connect (ambientMusic, SIGNAL(aboutToFinish()), this, SLOT(enqueueMediaObject()));
    ambientMusic->play();
}

void AudioManager::enqueueMediaObject()
{
    ambientMusic->enqueue(currentFileName);
}

void AudioManager::playEffect(int effectId)
{
    if(audioEnabled)
        effectsList.at(effectId)->play();
}

void AudioManager::run()
{
}
