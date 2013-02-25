#include "menu.h"
#include <SFML/Window.hpp>

#define forbtn(i) for (uint i = 0; i < buttons.size(); i++)



/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Menu::Menu()
{
    //ctor
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Menu::~Menu()
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
<<<<<<< HEAD:src/menu.cpp
=======
void Menu::newButton(std::string text, void *func())
{
    Button *btn = new Button();
    btn->setWidth(100);
    btn->setHeight(50);
    buttons.push_back(btn);
}

void Menu::addButton(Button*b)
{
    buttons.push_back(b);
}

void Menu::deleteButton(Button*b)
{
    for (uint i = 0; i < buttons.size(); i++)
    {
        if (buttons[i] == b)
        {
            delete buttons[i];
            buttons.erase(buttons.begin()+i);
        }
    }
}

void Menu::clearButton()
{
    while (buttons.size() > 0)
    {
        delete buttons[0];
        buttons.erase(buttons.begin());
    }
}



void Menu::update(sf::Vector2i mpos)
{
    forbtn(i)
    {
        if (buttons[i]->contains(mpos))
        {
            //buttons[i]->onClick(); //BUG: Undefined reference
        }
    }

}
>>>>>>> 8d4a79f8528b26c27db102a5d7a68ac46ce7768d:menu.cpp
