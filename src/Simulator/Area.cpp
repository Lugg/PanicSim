#include "../../include/Simulator/Area.hpp"

    ClArea::ClArea()
    {
        id = 0;
        time =0;
        fire_texture.loadFromFile("pictures/fire.png");
    }

    ClArea::~ClArea()
    {
        for(unsigned int n=0; n < sobjects.size(); n++)
        {
            delete sobjects[n];
        }
    }

    void ClArea::viewOnStaticObject()
    {
        for (int n=0; n<sobjects.size();n++)
        {
            if(sobjects[n]->getIsOnFire()== true && sobjects[n]->getIsChecked() == false) // looks for obejcts wich are on fire an not yet checked
            {

                    for (int m=0; m< sobjects.size(); m++)
                    {
                        if (sobjects[m]->IntersectsRectangle(sobjects[n]->biggerRect())== true&& sobjects[m]->getType() != GATE && sobjects[m]->getType() != FENCE)
                        {
                            sobjects[m]->startToBurn();
                        }

                    }

                sobjects[n]->setIsChecked(true);
            }
        }
         for (int n=0; n<sobjects.size();n++)
         {
             sobjects[n]->setfirstTime(false);
         }
    }

    float ClArea::addFrameTime(float frameTime)
    {
        time = time+frameTime;
        return time;
    }


    void ClArea::update(float frameTime)
    {
       if (addFrameTime(frameTime)>  10000 )
       {
           viewOnStaticObject();
           time =0; // to reset the counter
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
            if(sobjects[n] != 0) sobjects[n]->draw(window);
        }

    }
    bool ClArea::validPoint(sf::Vector2f point)
    {
        for( unsigned int n=0; n < sobjects.size(); n++)
        {
            if(sobjects[n]->getType() != GATE &&sobjects[n]->getType() != FENCE && sobjects[n]->Intersects(point))
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
//changed by Patrick (addaption for Pathfinding, to allow to walk over a Fence in Panik-mode)
    bool ClArea::isInvalidNode(sf::Vector2f node, int nodeDistance) // ensure that there are no nodes close to staticObjects
    {
        for(unsigned int n = 0; n < sobjects.size(); n++)
        {
            sf::Rect<float> testRect;

            testRect.top = node.y - nodeDistance/2;
            testRect.height = nodeDistance;
            testRect.left = node.x - nodeDistance/2;
            testRect.width = nodeDistance;

            if(sobjects[n]->IntersectsRectangle(testRect) && sobjects[n]->getType() != FENCE)
                return true;
        }
        return false;
    }

    bool ClArea::isValidId(int id)
    {
        if(this->getObject(id) == NULL) return false; return true;
    }

    bool ClArea::getOnFire(int id)
    {
        return getObject(id)->getOnFire();
    }

    void ClArea::setOnFire(int id)
    {
        time=0;
        for(unsigned int n = 0; n < sobjects.size(); n++)
        {
            if (sobjects[n]->getID() == id)
            {
                sobjects[n]->startToBurn();
            }
        }
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
        return NULL;
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
    //std::cerr << "Call of closestExit Y: " << myPosition.x << ", Y: " << myPosition.y << " \n";
    float distance = INFINITY;
    sf::Vector2f closestExitPosition;
    ClStaticObject *closestExit;
    for(unsigned int n = 0; n < sobjects.size(); n++)
    {
        if (sobjects[n]->getType() == GATE)
        {
            sf::Vector2f position = sobjects[n]->getCenter();
            float testDistance = (myPosition.x - position.x)*(myPosition.x - position.x)+(myPosition.y - position.y)*(myPosition.y - position.y);
            testDistance = sqrt(testDistance);
            if (testDistance<distance)
            {
                closestExitPosition = position;
                distance = testDistance;
                closestExit = sobjects[n];
            }
        }
    }

   // std::cerr << "Exit middle: " << closestExitPosition.x << ", " << closestExitPosition.y << "\n";
    int numOfExitPoints = closestExit->getSize().x / (EXIT_POINT_DISTANCE + 1);

    //Big exit with at minimum two exit points: choose nearest
    if(numOfExitPoints > 1)
    {
        ClExitPointSelection myExitSel;
        return myExitSel.getClosestExitPoint(closestExit,  myPosition, numOfExitPoints);

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
        return -1;
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
