#ifndef BUTTON_H
#define BUTTON_H


class Button
{
    public:
        Button();
        virtual ~Button();

        //setters
        void setWidth(int i);
        void setHeight(int i);
        void setPos(int a, int b);
    private:
        //vars
        int x, y, w, h;
        sf::Color bgColor;
        sf::Color fgColor;
        //function pointer
        void *onClick();     //can you make it so a click = mouseDown on button then mouseUp on button
};

#endif // BUTTON_H
