// Author: Francisco Andrade
// Date:   03/11/25
// File:   fandrade.cpp
//
// Contains code for implementing OpenAL sounds

#include <iostream>
#include "fonts.h"
#ifdef USE_OPENAL_SOUND
#include <AL/alut.h>
#endif //USE_OPENAL_SOUND

void show_francisco(Rect* r)
{
    ggprint8b(r, 16, 0x00ff00ff, "Francisco - The Creator");
}

#ifdef USE_OPENAL_SOUND
void init_openal()
{
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: alutInit()\n");
    }
    alGetError(); //Clear error state.
    
    //Setup the listener.
    //Forward and up vectors are used.
    //The person listening is facing forward toward the sound.
    //The first 3 components of vec are 0,0,1
    //this means that the person is facing x=0, y=0, z=1, forward.
    //The second 3 components means that up is x=0,y=1,z=0, straight up!
    float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);
}

/*
void playSong(string name)
{
    // if 
    alDeleteSources(1, source);
    alDeleteBuffers(1, buffer);

}

void playSFX(string name)
{

}

void changeSong(string name)
{

}
*/

void cleanup_openal(ALuint *source, ALuint *buffer)
{
    alDeleteSources(1, source);
    alDeleteBuffers(1, buffer);
    system("rm ./audio/music/*.wav");
    system("rm ./audio/sfx/*.wav");

    //Close out OpenAL itself
    //Get active context
    ALCcontext *Context = alcGetCurrentContext();
    //Get device for active context
    ALCdevice *Device = alcGetContextsDevice(Context);
    //Disable context
    alcMakeContextCurrent(NULL);
    //Release context
    alcDestroyContext(Context);
    //Close device
    alcCloseDevice(Device);
}
#endif //USE_OPENAL_SOUND

