#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

#include "StaticObject.hpp"
#include <vector>

enum staticObjects{STAGE, BAR, WC, WALL, FENCE};
const unsigned int MAXSTATICOBJECTTYPES = FENCE; // set this enum to the rightmost of all staticObjects

class ClArea
{
    public:

    ClArea() {id = 0;}
    ~ClArea();

    int insertStObj(enum staticObjects type, const sf::Vector2f & sizeOfRectangle,
                    const sf::Vector2f & positionOfRectangle, float rotAngle);
    void draw(sf::RenderWindow& window);
    bool validPoint(sf::Vector2f point); // returns whether a point is inside a staticObject ( false ) or not ( true )

    /// Get and Set for StaticObjects

    /// Get Methods for StaticObjects attributes via the id
    /// for the editor

    const sf::Vector2f & getPosition(int id);   // returns position of a StaticObject via id
    const sf::Vector2f & getSize(int id);       // returns size of a StaticObject via id
    float getRotation(int id);                  // returns rotation of a StaticObject via id


    /// Set Methods for StaticObjects attributes via id and new value
    /// for the editor

    void setPosition(int id, const sf::Vector2f &position);     // sets position of StaticObject via id
    void setSize(int id, const sf::Vector2f &newSize);          // sets size of StaticObject via id
    void setRotation(int id, float rotation);                   // sets rotation of StaticObject via id

    /// For the FileHandler
    int getNumberOfStaticObjects() {return id;}     // return total number of static objects
                                                    // ids of static objects start at id = 1 !!!
    int getType(int id);                            // returns Type of a StaticObject via id

    private:

    int id; // used to give StaticObjects a unique id
    std::vector<ClStaticObject *> sobjects;
};

#endif // AREA_HPP_INCLUDED
