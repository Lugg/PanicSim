/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creation of bombs, handling mouse action on bombs and set new position according to mouse position, activation
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef BOMB_HPP_INCLUDED
#define BOMB_HPP_INCLUDED

#include "Threat.hpp"

class ClBomb : public ClThreat
{
public:
    ClBomb(const sf::Vector2f &position_threat, const sf::Texture &texture_threat, ClArea *pArea, ClHeatMap *pHeatMap, ClStatistic *pStatistic,const sf::Texture &explosion_texture, ClDiagramm *pDiagramm);
    void recognizeMouse(sf::RenderWindow &window , const sf::Vector2i & mouseOffset);
    void activate();
    void draw(sf::RenderWindow &window);
};

#endif // BOMB_HPP_INCLUDED
