#include "creep.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Creep::Creep(int temp[][GRIDY])
{
    distances = temp;
    body.setSize({20, 20});
    body.setFillColor(sf::Color::Black);
    body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
    body.setPosition(coordinatePosition({0, GRIDY / 2}).x, coordinatePosition({0, GRIDY / 2}).y + BOXDIMENSIONS / 2);
//    body.setPosition(coordinatePosition({GRIDX * 2 + MIDDLE - 1, GRIDY / 2}).x + BOXDIMENSIONS, coordinatePosition({GRIDX * 2 + MIDDLE - 1, GRIDY / 2}).y + BOXDIMENSIONS / 2);
    targetPoint = body.getPosition();
}

Creep::Creep()
{
    //ctor
}

/***************************************************************/
/*******************DESTRUCTORS*********************************/
/***************************************************************/

Creep::~Creep()
{
    //dtor
}

/***************************************************************/
/*******************GETTERS*************************************/
/***************************************************************/

sf::Vector2i Creep::getCoordinates()
{
    return coordinates;
}

/***************************************************************/
/*******************SETTERS*************************************/
/***************************************************************/

/***************************************************************/
/*******************FUNCTIONS***********************************/
/***************************************************************/

void Creep::draw(sf::RenderTarget * target)
{
    target->draw(body);
}

void Creep::update()    //todo: check if trapped
{
    coordinates = gridPosition((sf::Vector2i)body.getPosition());

    sf::Vector2i temp = gridPosition((sf::Vector2i)targetPoint);
    bool targetFilled = false;
    if (distances[temp.x][temp.y] == FILLED)
    {
        targetFilled = true;
    }

    if (distance(targetPoint, body.getPosition()) < 5 || targetFilled)
    {
        int lowest = 9999;
        int possible = 0;
        sf::Vector2i next[4];

        if (coordinates.x > 0)
        {
            if (distances[coordinates.x - 1][coordinates.y] < lowest)
            {
                lowest = distances[coordinates.x - 1][coordinates.y];
                possible = 0;
                next[possible] = {coordinates.x - 1, coordinates.y};
            }
            else if (distances[coordinates.x - 1][coordinates.y] == lowest)
            {
                possible++;
                next[possible] = {coordinates.x - 1, coordinates.y};
            }
        }
        if (coordinates.x < GRIDX * 2 + MIDDLE - 1)
        {
            if (distances[coordinates.x + 1][coordinates.y] < lowest)
            {
                lowest = distances[coordinates.x + 1][coordinates.y];
                possible = 0;
                next[possible] = {coordinates.x + 1, coordinates.y};
            }
            else if (distances[coordinates.x + 1][coordinates.y] == lowest)
            {
                possible++;
                next[possible] = {coordinates.x + 1, coordinates.y};
            }
        }
        if (coordinates.y > 0)
        {
            if (distances[coordinates.x][coordinates.y - 1] < lowest)
            {
                lowest = distances[coordinates.x][coordinates.y - 1];
                possible = 0;
                next[possible] = {coordinates.x, coordinates.y - 1};
            }
            else if (distances[coordinates.x][coordinates.y - 1] == lowest)
            {
                possible++;
                next[possible] = {coordinates.x, coordinates.y - 1};
            }
        }
        if (coordinates.y < GRIDY - 1)
        {
            if (distances[coordinates.x][coordinates.y + 1] < lowest)
            {
                lowest = distances[coordinates.x][coordinates.y + 1];
                possible = 0;
                next[possible] = {coordinates.x, coordinates.y + 1};
            }
            else if (distances[coordinates.x][coordinates.y + 1] == lowest)
            {
                possible++;
                next[possible] = {coordinates.x, coordinates.y + 1};
            }
        }

        int choice = rand() % (possible + 1);
        targetPoint = (sf::Vector2f)coordinatePosition(next[choice]);
        targetPoint = {targetPoint.x + BOXDIMENSIONS / 2, targetPoint.y + BOXDIMENSIONS / 2};
    }

    if (body.getPosition().x - targetPoint.x > 3)
    {
        body.setPosition(body.getPosition().x - 2, body.getPosition().y);
    }
    else if (body.getPosition().x - targetPoint.x < -3)
    {
        body.setPosition(body.getPosition().x + 2, body.getPosition().y);
    }
    else if (body.getPosition().y - targetPoint.y > 3)
    {
        body.setPosition(body.getPosition().x, body.getPosition().y - 2);
    }
    else if (body.getPosition().y - targetPoint.y < -3)
    {
        body.setPosition(body.getPosition().x, body.getPosition().y + 2);
    }


        //print current distances
//    printf("\n");
//    printf("\n");
//
//    for(int a = 0; a < GRIDY; ++a)
//    {
//        for(int b = 0; b < GRIDX * 2 + MIDDLE; ++b)
//        {
//            if(distances[b][a] == FILLED)
//            {
//                printf("*  ");
//                continue;
//            }
//            printf("%d ", distances[b][a]);
//            if (distances[b][a] < 10)
//                printf(" ");
//        }
//        printf("\n");
//    }
}
