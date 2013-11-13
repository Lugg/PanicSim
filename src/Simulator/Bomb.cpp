/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creation of bombs, handling mouse action on bombs and set new position according to mouse position, activation
---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "../../include/Simulator/Bomb.hpp"

ClBomb::ClBomb(const sf::Vector2f &position_threat, const sf::Texture &texture_threat, ClArea *pArea, ClHeatMap *pHeatMap, ClStatistic *pStatistic, const sf::Texture &explosion_texture, ClDiagramm *pDiagramm)
{
    this->position_threat = position_threat;
    this->pArea = pArea;
    this->pHeatMap = pHeatMap;
    this->pStatistic = pStatistic;
    this->pDiagramm = pDiagramm;

//threat is movable, not active but alive at the beginning
    isActive = false;
    alive = true;
    isMoved = true;

//Threat gets this position and texture
    sprite_threat.setPosition(position_threat);
    sprite_threat.setTexture(texture_threat);

//"threat" is an IntRect which is used to calculate if the mouse is contained in the threat (recognizeMouse())
    threat.left = position_threat.x-(0.5*(sprite_threat.getGlobalBounds().width));
    threat.top = position_threat.y-(0.5*(sprite_threat.getGlobalBounds().height));
    threat.width = sprite_threat.getGlobalBounds().width;
    threat.height = sprite_threat.getGlobalBounds().height;

//set the origin in the middle of the threat
    sf::Vector2f sizeT(sprite_threat.getGlobalBounds().width, sprite_threat.getGlobalBounds().height);
    sprite_threat.setOrigin(sizeT.x/2,sizeT.y/2);

//set explosion texture
    explosion_sprite.setTexture(explosion_texture);
    subrect.top=0;
    subrect.left=0;
    subrect.width=explosion_texture.getSize().x/8;
    subrect.height=explosion_texture.getSize().y/8;
    bildID=0;

    type = THBOMB;
}

void ClBomb::draw(sf::RenderWindow &window)
{
    //draw the bomb
    window.draw(sprite_threat);
    //if the bomb has been activated
    if (isActive)
    {
        // 1. calculate picture number from time
        // 2. chose correct picture
        if (bildID > MAX_BILD_ID)
        {
            alive = false;
        }
        int time = animationTime.getElapsedTime().asMilliseconds();
        bildID = (int)time/PICTUREDURATION;
        subrecttoNumber(bildID);
        window.draw(explosion_sprite);
    }
}

void ClBomb::recognizeMouse(sf::RenderWindow &window , const sf::Vector2i &mouseOffset)
{
    //1. take position of mouse
    //2. if mouse is contained in IntRect "threat"
    //3. check if threat is moved actually
    //3.1       if threat is not moving - click causes start of move
    //3.2       if threat is moving -> 4.
    //4  click causes stop of move

    //1.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    mousePosition.x += mouseOffset.x;
    mousePosition.y += mouseOffset.y;
    //2.
    if(threat.contains(mousePosition))
    {
        //3.
        if(isMoved==false)
        {
            //3.1
            isMoved = true;
        }
        //3.2
        else
        {
            //4
            isMoved = false;
        }
    }
}

//activate bomb
void ClBomb::activate()
{
    //1. if it�s not active - activate bomb
    //2. remember casualties by bomb in HeatMap (statistic and diagramm)
    //3. restart clock for bomb activation
    //4. tell the statistics about activated bomb

    //1.
    if(isActive == false)
    {
        isActive = true;
        //2.
        int casualties = pHeatMap->explosion(sf::Vector2f(threat.left + (threat.width / 2), threat.top + (threat.height/2)), 100);
        //3.
        animationTime.restart();
        //4.
        //prototype: rememberThreats(bool type_bomb, bool type_fire)
        pStatistic->rememberThreats(true, false);
    }
}
