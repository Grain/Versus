#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "button.h"

class Menu      //Menu will be similar to Game, will have RenderTexture that everything gets rendered on, then gets converted into sprite for drawing on the window
{
    public:
        Menu();
        virtual ~Menu();

        vector<Button*> buttons;

        void newButton(string, void*func())
        void addButton(Button*);
        void deleteButton(Button*);
        void clearButton();
    private:
};


#endif // MENU_H
