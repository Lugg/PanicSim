#include "../../include/Simulator/Area.hpp"


    ClArea::ClArea()
    {id = 0;
    fire_texture.loadFromFile("pictures/fire.png");
    }

    ClArea::~ClArea()
    {
        for(unsigned int n=0; n < sobjects.size(); n++)
        {
            delete sobjects[n];
        }
    }

    int ClArea::insertStObj(enum staticObjects type, const sf::Vector2f & sizeOfRectangle,
                            const sf::Vector2f & positionOfRectangle, float rotAngle)
    {
        id++;
        sf::RectangleShape *tempRe = new sf::RectangleShape();
        tempRe->setPosition(positionOfRectangle);
        tempRe->setSize(sizeOfRectangle);
        tempRe->setRotation(rotAngle);
        if(type == GATE)
            tempRe->setFillColor(sf::Color::Red);
        ClStaticObject *tempSt = new ClStaticObject(tempRe, id, type,fire_texture);
        sobjects.push_back(tempSt);
        return id;
    }


    void ClArea::draw(sf::RenderWindow& window)
    {
        for(unsigned int n=0; n < sobjects.size(); n++)
        {
            if(sobjects[n] != 0)
                sobjects[n]->draw(window);

        }
/*
        sf::CircleShape exitPoint;

    exitPoint.setFillColor(sf::Color(255,255,0));
    exitPoint.setRadius(5);
    exitPoint.setOrigin(2.5,2.5);

    sf::Vector2f avgPosition;

    for(unsigned int n = 0; n< exitPoints.size(); n++)
    {
        exitPoint.setPosition(exitPoints[n]);
        window.draw(exitPoint);
    }
*/
    }
    bool ClArea::validPoint(sf::Vector2f point)
    {
        for( unsigned int n=0; n < sobjects.size(); n++)
        {
            if(sobjects[n]->getType() != GATE && sobjects[n]->Intersects(point))
            {
                return false;
            }
        }
        return true;
    }

    bool ClArea::validPath(sf::Vector2f startPoint, sf::Vector2f endPoint)
    {
        for( unsigned int n=0; n < sobjects.size(); n++)
        {
            if(sobjects[n]->isValidPath(startPoint, endPoint))
            {
                return false;
            }
        }
         return true;
    }

/// Get Methods for static Object attributes via the id
/// for the editor

    const sf::Vector2f & ClArea::getPosition(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getPosition();
            }
        }
    }

    ClStaticObject * ClArea::getObject(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n];
            }
        }
    }

    bool ClArea::attractionWithHigherId(int lId)
    {
        if(getType(lId) <= 2)
        {
            return true;
        }
        else
        {
            if(lId < id)
            {
                return this->attractionWithHigherId(lId + 1);
            }
            else
            {
                return false;
            }
        }
    }

const sf::Vector2f ClArea::getClosestExit(const sf::Vector2f & myPosition)
{
    std::cerr << "Call of closestExit Y: " << myPosition.x << ", Y: " << myPosition.y << " \n";
    float distance = INFINITY;
    sf::Vector2f closestExitPosition;
    ClStaticObject *closestExit;
    for(unsigned int n = 0; n < sobjects.size(); n++)
    {
        if (sobjects[n]->getType() == GATE)
        {
            sf::Vector2f position = sobjects[n]->getCenter();
            float testDistance = (myPosition.x - position.x)*(myPosition.x - position.x)+(myPosition.y - position.y)*(myPosition.x - position.x);
            if (testDistance<distance)
            {
                closestExitPosition = position;
                distance = testDistance;
                closestExit = sobjects[n];
            }

        }
    }
    std::cerr << "Exit middle: " << closestExitPosition.x << ", " << closestExitPosition.y << "\n";
    //Big exit with at minimum two exit points: choose nearest
    if(closestExit->getSize().x > EXIT_POINT_DISTANCE * 1.5)
    {
        distance = INFINITY;
        float testDistance = 0;
        int numOfExitPoints = closestExit->getSize().x / (EXIT_POINT_DISTANCE + 1);
        sf::Vector2f mainPoint = closestExit->getMiddleOfLine();
        sf::Vector2f centerPoint = closestExit->getCenter();
        sf::Vector2f diffVect = sf::Vector2f(mainPoint.x - centerPoint.x, mainPoint.y - centerPoint.y);
        sf::Vector2f unitVect;
        sf::Vector2f attrPosWa;
        ClFastSquareroot fSR;
        float vectorDistance = fSR.getSqrt((diffVect.x) * (diffVect.x) + (diffVect.y) * (diffVect.y));
        if(vectorDistance != 0)
        {
            unitVect.x = diffVect.x / vectorDistance;
            unitVect.y = diffVect.y / vectorDistance;
        }
        else
        {
            std::cout << "Division by zero when calculating the Unit vector.";
        }
        std::cerr << "UnitVect: X: " << unitVect.x << ", Y: " << unitVect.y << "\n";

        if(abs(unitVect.x) < abs(unitVect.y))
        {
            mainPoint.x -= numOfExitPoints * EXIT_POINT_DISTANCE / 2 - EXIT_POINT_DISTANCE / 2;
        }
        else
        {
            mainPoint.y -= numOfExitPoints * EXIT_POINT_DISTANCE / 2 - EXIT_POINT_DISTANCE / 2;
        }

        attrPosWa = mainPoint;
        for(int i = 0; i < numOfExitPoints; i++)
        {
            testDistance = (myPosition.x - attrPosWa.x)
            *(myPosition.x - attrPosWa.x)
            +(myPosition.y - attrPosWa.y)
            *(myPosition.x - attrPosWa.x);
            if (testDistance<distance)
            {
                mainPoint = attrPosWa;
                closestExitPosition = mainPoint;
                distance = testDistance;
            }
            //exitPoints.push_back(sf::Vector2f(attrPosWa.x - diffVect.x, attrPosWa.y - diffVect.y));
            if(abs(unitVect.x) < abs(unitVect.y))
            {
                attrPosWa.x += EXIT_POINT_DISTANCE;
            }
            else
            {
                attrPosWa.y += EXIT_POINT_DISTANCE;
            }
            std::cerr << "Iteration: " << i << "; X: " << closestExitPosition.x << ", Y:" << closestExitPosition.y << "\n";
        }

            closestExitPosition.x -= diffVect.x;
            closestExitPosition.y -= diffVect.y;
        std::cerr << "Returned value: " << closestExitPosition.x << ", " << closestExitPosition.y << "\n";
        return closestExitPosition;
    }
    else
    {
        //Small exit with just one exit point, so no further checks are necessary
        return closestExitPosition;
    }
}


    const sf::Vector2f & ClArea::getSize(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getSize();
            }
        }
    }
    float ClArea::getRotation(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getRotation();
            }
        }
    }

    enum staticObjects ClArea::getType(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getType();
            }
        }
    }

     int  ClArea::getIdByVector(sf::Vector2f mouse)
     {
        for( unsigned int n=0; n < sobjects.size(); n++)
        {
            if(sobjects[n]->Intersects(mouse))
            {
                return sobjects[n]->getID();
            }
        }
        return -1;
     }
    /// not for the editor

    const sf::Vector2f & ClArea::getSource(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getCenter();
            }
        }
    }


    /// Set Methods for StaticObjects attributes via id and new value
    /// for the editor

    void ClArea::setPosition(int id, const sf::Vector2f &position) // sets position of StaticObject via id
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                sobjects[n]->setPosition(position);
            }
        }
    }
    void ClArea::setSize(int id, const sf::Vector2f &newSize)         // sets size of StaticObject via id
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                sobjects[n]->setSize(newSize);
            }
        }
    }
    void ClArea::setRotation(int id, float rotation)               // sets rotation of StaticObject via id
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                sobjects[n]->setRotation(rotation);
            }
        }
    }

    /// Remove static Object
    bool ClArea::removeObj(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id){
                delete sobjects[n];
                sobjects.erase(sobjects.begin()+n);
                return true;
            }
        }
        return false;
    }
