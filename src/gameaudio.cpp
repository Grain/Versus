#include "gameaudio.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

GameAudio::GameAudio()
{
    music.openFromFile("resources/music.wav");  //from http://freesound.org/people/djgriffin/sounds/172561/
    music.setLoop(true);
    music.setVolume(settings.musicVolume * 10);
    music.play();

    char temp[30];
    for(int i = 0; i < 12; ++i)
    {
        sprintf(temp, "resources/hit%d.wav", i);
        buffer[i].loadFromFile(temp);
    }

    buffer[12].loadFromFile("resources/sell.wav");
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

GameAudio::~GameAudio()
{
    //dtor
}

/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

void GameAudio::update()
{
    music.setVolume(settings.musicVolume * 10);
    for (int i = 0; i < 255; ++i)
    {
        sounds[i].setVolume(settings.effectVolume * 10);
    }
}

void GameAudio::play(GameAudio::sound a)
{
    for (int i = 0; i < 255; ++i)
    {
        if (sounds[i].getStatus() != sf::Sound::Playing)    //found empty slot
        {
            sounds[i].setBuffer(buffer[a]);
            sounds[i].play();
            break;
        }
    }
}

void GameAudio::pause()
{
    music.pause();
}

void GameAudio::resume()
{
    music.play();
}
