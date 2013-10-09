#include <SFML/Graphics.hpp>
#ifndef C_STATIC_OBJECT_INCLUDE
#define C_STATIC_OBJECT_INCLUDE

#include <iostream>
#include <math.h>

class ClStaticObject
{
public:
    ClStaticObject(sf::RectangleShape *Rectconst, int id, int Type);
    ~ClStaticObject();
    void draw(sf::RenderWindow& window);

    bool Intersects( const sf::Vector2f  &Position); // returns true if Position is inside of the StaticObject
    int getID();
    int getType();
    const sf::Vector2f &getPosition();
    const sf::Vector2f &getSize();

    float getRotation();

    void setPosition(const sf::Vector2f &position);
    void setRotation(float rotation);
    void setSize(const sf::Vector2f &newSize);

private:
    int Type;
    sf::RectangleShape *Rect;
    int id; // unique id
};

#endif // C_STATIC_OBJECT_INCLUDE
