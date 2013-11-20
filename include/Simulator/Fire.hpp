/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creation of fire, handling mouse action on fire and set new position according to mouse position, activation
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef FIRE_HPP_INCLUDED
#define FIRE_HPP_INCLUDED

#include "Threat.hpp"

class ClFire : public ClThreat
{
public:
    ClFire(const sf::Vector2f &position_threat, const sf::Texture &texture_threat, ClArea *pArea, ClHeatMap *pHeatMap, ClStatistic *pStatistic, ClDiagramm *pDiagramm);
    void recognizeMouse(sf::RenderWindow &window , const sf::Vector2i & mouseOffset);
    void activate();
    void draw(sf::RenderWindow &window);
};

#endif // FIRE_HPP_INCLUDED
