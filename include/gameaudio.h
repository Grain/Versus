#ifndef GAMEAUDIO_H
#define GAMEAUDIO_H

#include "global.h"
#include <SFML/Audio.hpp>

class GameAudio
{
    public:
        //types of sound effects
        enum sound{hit0, hit1, hit2, hit3, hit4, hit5, hit6, hit7, hit8, hit9, hit10, hit11, sell};
        //ctor/dtor
        GameAudio();
        virtual ~GameAudio();
        //functions
        void update();
        void play(GameAudio::sound);
        void pause();
        void resume();
    protected:
    private:
        sf::Music music;
        sf::Sound sounds[255];
        sf::SoundBuffer buffer[255];
};

#endif // GAMEAUDIO_H
