#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

struct Keys
{
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key select;
    sf::Keyboard::Key back;
};

struct Settings
{
    Keys leftPlayer, rightPlayer;
    int effectVolume, musicVolume;
    bool enableMouseTwoPlayer;
};


#endif // GLOBAL_H_INCLUDED
