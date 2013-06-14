#include "creep.h"

/***************************************************************/
/*******************CONSTRUCTORS********************************/
/***************************************************************/

Creep::Creep(int temp[][GRIDY], int i, int tempType, int tempSpeed, int tempHp, sf::Texture * buff0, sf::Texture * buff1, sf::Texture * buff2, sf::Texture * buff3, sf::Texture * buff4, sf::Texture * tempBody, int tempSide)
{
    side = i;
    distances = temp;
    body.setSize({20, 20});
    body.setOrigin(body.getSize().x / 2, body.getSize().y / 2);

    bodyTexture = tempBody;

    body.setTexture(bodyTexture, true);
    animation = 0;
    body.setTextureRect(sf::IntRect(animation, 0, body.getSize().x, body.getSize().y));

    if (tempSide == 0)
        health.setFillColor(sf::Color::Red);
    else
        health.setFillColor(sf::Color::Green);
    health.setSize({body.getSize().x, HEALTHHEIGHT});
    health.setPosition({body.getGlobalBounds().left, body.getGlobalBounds().top - health.getSize().y - HEALTHDISTANCE});
    healthOutline.setSize({body.getSize().x, HEALTHHEIGHT});
    healthOutline.setPosition(health.getPosition());
    healthOutline.setOutlineColor(sf::Color::Black);
    healthOutline.setOutlineThickness(1);
    healthOutline.setFillColor(sf::Color::Black);

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

    buffTextures[0] = buff0;
    buffTextures[1] = buff1;
    buffTextures[2] = buff2;
    buffTextures[3] = buff3;
    buffTextures[4] = buff4;

    for (int i = 0; i < 5; ++i)
    {
        buffs[i].x = 0;
        buffs[i].y = 0;
        buffIcons[i].setTexture(buffTextures[i]);
        buffIcons[i].setSize({4, 4});
    }

    targetPoint = body.getPosition();

    maxHp = tempHp;
    hp = maxHp;
    dead = false;
    speed = tempSpeed;      //speeds > 6 or so should fail miserably. speed = 7 SEEMS to work, but 6 should be the limit, i think
    type = tempType;

    bigProgress = 0;
    smallProgress = 0;
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

sf::FloatRect Creep::getGlobalBounds()
{
    return body.getGlobalBounds();
}

bool Creep::isDead()
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

    for (int i = 0; i < 5; ++i)
    {
        if (buffs[i].x > 0)
        {
            target->draw(buffIcons[i]);
        }
    }
}

int Creep::update()
{
    if (hp <= 0)
    {
        dead = true;
        return 0;
    }

    for (int i = 0; i < 2; ++i) //so creeps can move faster but still have good resolution for checking distances/collisions/stuff
    {
        coordinates = gridPosition((sf::Vector2i)body.getPosition());

        sf::Vector2i temp = gridPosition((sf::Vector2i)targetPoint);
        bool targetFilled = false;
        if (distances[temp.x][temp.y] == FILLED)
        {
            targetFilled = true;
        }

        if (distances[coordinates.x][coordinates.y] == EMPTY)
        {
            return 1;
        }

        smallProgress = distance(targetPoint, body.getPosition());

        if (smallProgress < 5 || targetFilled)  //find next target location
        {
            if (coordinates == enemy)   //reached enemy base
            {
                dead = true;
                return 2;
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

        double multiplier = 1;
        if (buffs[1].x > 0) //slow
        {
            multiplier -= buffs[1].y / 100.0;
        }
        if (buffs[4].x > 0) //speed
        {
            multiplier += buffs[4].y / 100.0;
        }
        double tempSpeed = speed * multiplier;

        if (tempSpeed > 6)
            tempSpeed = 6;

        if (body.getPosition().x - targetPoint.x > 3)   //left
        {
            body.setPosition(body.getPosition().x - tempSpeed, body.getPosition().y);
            body.setRotation(270);
        }
        else if (body.getPosition().x - targetPoint.x < -3) //right
        {
            body.setPosition(body.getPosition().x + tempSpeed, body.getPosition().y);
            body.setRotation(90);
        }
        else if (body.getPosition().y - targetPoint.y > 3)  //up
        {
            body.setPosition(body.getPosition().x, body.getPosition().y - tempSpeed);
            body.setRotation(0);
        }
        else if (body.getPosition().y - targetPoint.y < -3)    //down
        {
            body.setPosition(body.getPosition().x, body.getPosition().y + tempSpeed);
            body.setRotation(180);
        }
    }

    for (int i = 0; i < 5; ++i)
    {
        if (buffs[i].x > 0)
        {
            buffs[i].x--;
            buffIcons[i].setPosition(body.getGlobalBounds().left + i * buffIcons[i].getSize().x, body.getGlobalBounds().top + body.getGlobalBounds().height + 2);
        }
    }

    if (buffs[3].x > 0) //regen
    {
        if ((buffs[3].x % (FPS / 2)) == 0)   //tick twice a second
        {
            heal(buffs[3].y / 2);
        }
    }

    health.setSize({(((float)hp / (float)maxHp) * (float)healthOutline.getSize().x), HEALTHHEIGHT});

    health.setPosition({body.getGlobalBounds().left, body.getGlobalBounds().top - health.getSize().y - HEALTHDISTANCE});
    healthOutline.setPosition(health.getPosition());

    animation += body.getSize().x;
    if (animation > bodyTexture->getSize().x - body.getSize().x)
        animation = 0;
    body.setTextureRect(sf::IntRect(animation, 0, body.getSize().x, body.getSize().y));

    coordinates = gridPosition((sf::Vector2i)body.getPosition());

    return 0;
}

void Creep::damage(int i)
{
    double temp = 1;
    if (buffs[0].x > 0) //damage amp
    {
        temp += buffs[0].y / 100.0;
    }
    if (buffs[2].x > 0) //damage reduction
    {
        temp -= buffs[2].y / 100.0;
    }

    hp -= (int)((double)i * temp);

    if (hp > maxHp)
    {
        hp = maxHp;
    }
}

void Creep::heal(int i)
{
    hp += i;

    if (hp > maxHp)
    {
        hp = maxHp;
    }
}

void Creep::buff(int tempType, int tempSeverity)
{
    if (tempType > 1)
    {
        buffs[tempType].x = 10 * FPS;   //10 secs for buffs
    }
    else
    {
        buffs[tempType].x = 3 * FPS;   //3 secs for debuffs
    }

    buffs[tempType].y = tempSeverity;
}
