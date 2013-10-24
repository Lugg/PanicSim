#include "../../include/Simulator/StaticObject.hpp"
#include <math.h>

ClStaticObject::ClStaticObject(sf::RectangleShape *Rectconst, int id, int Type)
{

    sf::Vector2f RectSize = Rectconst->getSize();
    Rect = Rectconst;
    this->Type = Type;

    this->id = id;

    Rect->setOrigin(Rect->getSize().x/2,Rect->getSize().y/2);
    text.setPosition(Rect->getPosition().x,Rect->getPosition().y);
    getTextfromType(Type);
    font.loadFromFile("fonts/LiberationSerif-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(60);
    text.setColor(sf::Color::Black);


    text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height);

    if(Rect->getRotation()>90 && Rect->getRotation()<271)
        {
        text.setRotation(Rect->getRotation()-180);
        }
        else
        {
            text.setRotation(Rect->getRotation());
        }

    while((Rect->getSize().x<text.getLocalBounds().width || Rect->getSize().y< text.getLocalBounds().height) && text.getCharacterSize()> 30)
    {
            text.setCharacterSize(text.getCharacterSize()-1);
            text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height);

    }

    if(Type!=FENCE && Type!=WALL)
    {
        line.setSize(sf::Vector2f(Rect->getSize().x,5));
        line.setFillColor(sf::Color::Red);
        line.setPosition(Rect->getPosition());
        line.setOrigin(Rect->getSize().x/2,-Rect->getSize().y/2+line.getSize().y);
        line.setRotation(Rect->getRotation());
    }



}
int ClStaticObject::getType()
{
    return Type;
}

ClStaticObject::~ClStaticObject()
{
    delete Rect;
}

void ClStaticObject::draw(sf::RenderWindow& window)
{

    window.draw(*Rect);

    window.draw(line);
    window.draw(text);

}
bool ClStaticObject::Intersects( const sf::Vector2f  &Position)
    {
        return Rect->getGlobalBounds().contains(Position);
    }
    int ClStaticObject::getID()
    {
        return id;
    }
    const sf::Vector2f &ClStaticObject::getPosition()
    {
        return Rect->getPosition();
    }
    const sf::Vector2f &ClStaticObject::getSize()
    {
        return Rect->getSize();
    }

    float ClStaticObject::getRotation()
    {
        return Rect->getRotation();
    }

    void ClStaticObject::setPosition(const sf::Vector2f &position)
    {
                Rect->setPosition(position);
                settext();
    }
    void ClStaticObject::setRotation(float rotation)
    {
        Rect->setRotation(rotation);
        settext();
    }
    void ClStaticObject::setSize(const sf::Vector2f &newSize)
    {
        Rect->setSize(newSize);
        settext();
    }

    void ClStaticObject::getTextfromType(int type)
    {
      switch(type)
        {
        case STAGE:
            text.setString("Stage");
            break;
        case BAR:
            text.setString("Bar");
            break;
        case WC:
            text.setString("WC");
            break;
        case WALL:
            text.setString("Wall");
            break;
        case FENCE:
            text.setString("Fence");
            break;
        case GATE:
            text.setString("Exit");
            break;
        }
    }

   sf::Vector2f ClStaticObject::getCenter()
   {
      return Rect->getPosition();
   }

   void ClStaticObject::settext()
   {
    Rect->setOrigin(Rect->getSize().x/2,Rect->getSize().y/2);
    text.setPosition(Rect->getPosition().x,Rect->getPosition().y);
    getTextfromType(Type);
    font.loadFromFile("fonts/LiberationSerif-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(60);
    text.setColor(sf::Color::Black);


    text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height);

    if(Rect->getRotation()>90 && Rect->getRotation()<271)
        {
        text.setRotation(Rect->getRotation()-180);
        }
        else
        {
            text.setRotation(Rect->getRotation());
        }

    while((Rect->getSize().x<text.getLocalBounds().width || Rect->getSize().y< text.getLocalBounds().height) && text.getCharacterSize()> 30)
    {
            text.setCharacterSize(text.getCharacterSize()-1);
            text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height);

    }

    if(Type!=FENCE && Type!=WALL)
    {
        line.setSize(sf::Vector2f(Rect->getSize().x,5));
        line.setFillColor(sf::Color::Red);
        line.setPosition(Rect->getPosition());
        line.setOrigin(Rect->getSize().x/2,-Rect->getSize().y/2+line.getSize().y);
        line.setRotation(Rect->getRotation());
    }
   }

