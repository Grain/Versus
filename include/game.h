#ifndef GAME_H
#define GAME_H

#include "global.h"
#include "tower.h"
#include "button.h"
#include "creep.h"
#include "projectile.h"
#include <vector>
#include <queue>

class Game
{
    public:
        //enums
        enum Players{left, right, both};

        //ctor/dtor
        Game();
        virtual ~Game();
        //getters
        //setters

        //functions
        int update(sf::Vector2i);
        void draw(sf::RenderWindow*);
        void newGame(Players, sf::Color, sf::Color, sf::Color, sf::Color);
    protected:
    private:
        static const int FILLED = 99999;
        static const int EMPTY = 9999;

        struct KeyState
        {
            bool left;
            bool right;
            bool up;
            bool down;
            bool select;
            bool back;
            bool hotkey1;
            bool hotkey2;
            bool hotkey3;
            bool hotkey4;
        };

        //functions
        void initializeGrid(sf::RenderTarget*, sf::Color, sf::Color);
        void newTower(sf::Vector2i, int);
        void calculateDistances();
        std::string formatTime(int);
        bool fastForwardDown(sf::Vector2i);
        void mouseSelector(sf::Vector2i);
        void keyboardSelector(sf::Vector2i);    //updateKeyboard would be a better name...
        void buttonPressed(int, int);
        void removeTower(sf::Vector2i);
        Tower * towerAt(sf::Vector2i);
        void updateButtons(int);

        //vars
        Players players;
        sf::Vector2i prevMouse;
        KeyState prevKeys[2];
        sf::Texture selectorTextures[2];
        sf::RectangleShape selector[2];
        sf::Vector2i selectorCoordinates[2];

        bool selected[2];
        Button gameButtons[2][11];  //0 - 3: creep queue, 4 - 7: buttons, 8 - 10: creeps;
        sf::RectangleShape buttonSelector[2];   //for the middle row of buttons
        int middleCoordinates[2];   //for middle row of buttons
        bool outOfGrid[2];  //if primary selector is outside of grid
        sf::RectangleShape otherButtonSelector[2];  //the..other one            //this one is for the top and bottom row of buttons
        int buttonCoordinates[2];

        sf::RenderTexture canvas;
        sf::Sprite drawable;

        sf::RectangleShape background;
        sf::Texture backgroundTexture;

        std::vector<Tower*> towers;
        bool map[GRIDX * 2 + MIDDLE][GRIDY];
        sf::CircleShape ranges[2];
        bool visibleRanges[2];

        int distancesLeft[GRIDX * 2 + MIDDLE][GRIDY];   //left = going to left side, right = going to right side
        int distancesRight[GRIDX * 2 + MIDDLE][GRIDY];

        double time;
        sf::Text timer;
        sf::RectangleShape timerBackground;
        sf::RectangleShape timerBar;

        sf::RectangleShape speedBackground;
        sf::RectangleShape fastForward;
        sf::Texture fastForwardTexture;
        sf::Texture speedBackgroundTexture;
        unsigned int speedUpAnimation;
        int speedUp;

        Button pause;
        Button resume;
        Button exit;
        sf::RectangleShape pauseBackground;
        bool paused;
        bool prevEscape;

        std::vector<Creep*> creeps[2];
        std::vector<Projectile*> projectiles;

        sf::Color leftColor, rightColor;
        int money[2];
        sf::Text moneyText[2];
};

#endif // GAME_H
