#include "creep.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Creep::Creep(int temp[][GRIDY], int i)
{
    side = i;
    distances = temp;
    body.setSize({20, 20});
    body.setFillColor(sf::Color::Black);
    body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);
    bodyTexture.loadFromFile("resources/creep.png");
    body.setTexture(&bodyTexture, true);
    animation = 0;
    body.setTextureRect(sf::IntRect(animation, 0, body.getSize().x, body.getSize().y));

    health.setFillColor(sf::Color::Red);
    health.setSize({body.getSize().x, HEALTHHEIGHT});
    health.setPosition({body.getGlobalBounds().left, body.getGlobalBounds().top - health.getSize().y - HEALTHDISTANCE});
    healthOutline.setSize({body.getSize().x, HEALTHHEIGHT});
    healthOutline.setPosition(health.getPosition());
    healthOutline.setOutlineColor(sf::Color::Black);
    healthOutline.setOutlineThickness(1);
    healthOutline.setFillColor(sf::Color::Transparent);

    if (side == 0)
    {
        body.setPosition(coordinatePosition({0, GRIDY / 2}).x, coordinatePosition({0, GRIDY / 2}).y + BOXDIMENSIONS / 2);
        enemy = {GRIDX * 2 + MIDDLE - 1, GRIDY / 2};
    }
    else if (side == 1)
    {
        body.setPosition(coordinatePosition({GRIDX * 2 + MIDDLE - 1, GRIDY / 2}).x + BOXDIMENSIONS, coordinatePosition({GRIDX * 2 + MIDDLE - 1, GRIDY / 2}).y + BOXDIMENSIONS / 2);
        enemy = {0, GRIDY / 2};
    }

    targetPoint = body.getPosition();

    maxHp = 100;
    hp = maxHp;
    dead = false;
    speed = 1;
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

sf::Vector2f Creep::getPosition()
{
    return body.getPosition();
}

//used so towers can tell which creep is closest to base
//check bigProgress first, only check smallProgress if bigProgress is same
sf::Vector2i Creep::getProgress()
{
    return {bigProgress, (int)smallProgress};
}

bool Creep::isDead()    //make sure creep is not deleted for 1 frame after dying so projectiles know about it
{
    return dead;
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
    target->draw(healthOutline);
    target->draw(health);
}

void Creep::update()    //todo: check if trapped
{
    if (hp <= 0)
    {
        dead = true;
        return;
    }

    for (int i = 0; i < 2; ++i) //so creeps can move faster but still have good resolution for checking distances/collisions/stuff
    {
        coordinates = gridPosition((sf::Vector2i)body.getPosition());

        sf::Vector2i temp = gridPosition((sf::Vector2i)targetPoint);
        bool targetFilled = false;
        if (distances[temp.x][temp.y] == FILLED)    //bug: if the timing is perfect creep can go through tower
        {
            targetFilled = true;
        }

        smallProgress = distance(targetPoint, body.getPosition());

        if (smallProgress < 5 || targetFilled)  //find next target location
        {
            if (coordinates == enemy)
            {
                dead = true;
                return;
            }

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
            bigProgress = lowest;
            targetPoint = (sf::Vector2f)coordinatePosition(next[choice]);
            targetPoint = {targetPoint.x + BOXDIMENSIONS / 2, targetPoint.y + BOXDIMENSIONS / 2};
        }

        if (body.getPosition().x - targetPoint.x > 3)   //left
        {
            body.setPosition(body.getPosition().x - speed, body.getPosition().y);
            body.setRotation(270);
        }
        else if (body.getPosition().x - targetPoint.x < -3) //right
        {
            body.setPosition(body.getPosition().x + speed, body.getPosition().y);
            body.setRotation(90);
        }
        else if (body.getPosition().y - targetPoint.y > 3)  //up
        {
            body.setPosition(body.getPosition().x, body.getPosition().y - speed);
            body.setRotation(0);
        }
        else if (body.getPosition().y - targetPoint.y < -3)    //down
        {
            body.setPosition(body.getPosition().x, body.getPosition().y + speed);
            body.setRotation(180);
        }
    }

    health.setSize({(((float)hp / (float)maxHp) * (float)healthOutline.getSize().x), HEALTHHEIGHT});

    health.setPosition({body.getGlobalBounds().left, body.getGlobalBounds().top - health.getSize().y - HEALTHDISTANCE});
    healthOutline.setPosition(health.getPosition());

    animation += body.getSize().x;
    if (animation > bodyTexture.getSize().x - body.getSize().x)
        animation = 0;
    body.setTextureRect(sf::IntRect(animation, 0, body.getSize().x, body.getSize().y));

    coordinates = gridPosition((sf::Vector2i)body.getPosition());

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

void Creep::damage(int i)
{
    hp -= i;
    if (hp <= 0)
    {
        dead = true;
    }
}
