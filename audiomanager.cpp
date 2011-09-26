#include "audiomanager.h"


AudioManager::AudioManager(QObject *parent)
{

}

AudioManager::~AudioManager()
{

}

void AudioManager::enableAudio(GLboolean enabled)
{
    audioEnabled = enabled;
}

void AudioManager::playAmbientMusic(QString filename)
{
   // if (!audioEnabled)
     //   return;
     QSound::play(filename);
}

void AudioManager::pauseAmbientMusic()
{
}

void AudioManager::continueAmbientMusic()
{

}

void AudioManager::playEffect(GLint effectId)
{

}

void AudioManager::run()
{

}
