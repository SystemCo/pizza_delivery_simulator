#ifndef _FANDRADE_H_
#define _FANDRADE_H_

void show_francisco(Rect* r);
#ifdef USE_OPENAL_SOUND
void init_openal();
void cleanup_openal(ALuint *src, ALuint *buf);
#endif //USE_OPENAL_SOUND

#endif // _FANDRADE_H_
