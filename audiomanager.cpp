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
    if (ambientMusic != NULL)
        ambientMusic->clear();

    currentFileName = filename;
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
