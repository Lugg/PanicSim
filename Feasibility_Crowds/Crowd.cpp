#include "Crowd.hpp"


ClCrowd::ClCrowd(float radius, ClArea * area, sf::Color Color, sf::Vector2f position)
{
    this->position = position;
    this->Color = Color;

    this->radius = radius;
    sf::Vector2f mP = this->getMassPoint();
    Area = area;

    //randomize the position of the people
    for (int n = 0; n < MAXPPL; n++)
    {
        peoples[n].position.x = std::rand();
        peoples[n].position.x = (int)peoples[n].position.x % (int)(2*radius);
        peoples[n].position.x -= radius;
        peoples[n].position.y = std::rand();
        peoples[n].position.y = (int)peoples[n].position.y % (int)(2*radius);
        peoples[n].position.y -= radius;

        peoples[n].position.x += mP.x;
        peoples[n].position.y += mP.y;

        peoples[n].forceVec.x = peoples[n].forceVec.y =0;


    }

}
ClCrowd::~ClCrowd() {}

void  ClCrowd::Update(float frameTime)
{

    j++;
    float radius = 150;
    sf::Vector2f mP = this->getMassPoint();

    for (int n = 0; n < MAXPPL; n++)
    {
        if(j%2)
        {
            peoples[n].forceVec =  Seek( peoples[n].position, this->getMassPoint(), peoples[n].forceVec);
            peoples[n].forceVec.x *= 2;
            peoples[n].forceVec.y *= 2;
        }
        else
        {
            peoples[n].forceVec = DistanceForce(peoples, n);
            peoples[n].forceVec.x *= 2.5;
            peoples[n].forceVec.y *= 2.5;
        }
        peoples[n].position.x += peoples[n].forceVec.x * frameTime *0.1;
        peoples[n].position.y += peoples[n].forceVec.y * frameTime *0.1;

  //      if (radius < sqrt(((peoples[n].position.x - mP.x)*(peoples[n].position.x - mP.x))+
  //                       ((peoples[n].position.y - mP.y)*(peoples[n].position.y - mP.y))))
  //      {
  //          peoples[n].position.x = mP.x;
  //          peoples[n].position.y = mP.y;
  //      }

        if(!Area->ValidPoint(peoples[n].position))
        {
        peoples[n].position.x -= peoples[n].forceVec.x * frameTime;
        peoples[n].position.y -= peoples[n].forceVec.y * frameTime;
        }


    }


}
void  ClCrowd::Update(sf::Vector2i position,float frameTime)
{
    this->Update(frameTime);
    this->position.x = position.x;
    this->position.y = position.y;
}
void  ClCrowd::Draw(sf::RenderWindow& window)
{
    sf::CircleShape personShape;

    personShape.setFillColor(Color);
    personShape.setRadius(1);
    for(int n = 0; n< MAXPPL; n++)
    {
        personShape.setPosition(peoples[n].position);
        window.draw(personShape);
    }
    personShape.setPosition(getMassPoint());
    personShape.setFillColor(sf::Color::Red);
    personShape.setRadius(5);
    personShape.move(sf::Vector2f(-2.5,-2.5));
    window.draw(personShape);
}

const sf::Vector2f ClCrowd::getMassPoint()
{
    sf::Vector2f massPoint;
    massPoint = position;
    massPoint.x -= radius;
    massPoint.y -= radius;
    return massPoint;
}

float ClCrowd::getRadius()
{
    return radius;
}


void ClCrowd::Vec2DNormalize( sf::Vector2f *NormalizeMe )
{
    if (NormalizeMe->x != 0 && NormalizeMe->y != 0)
    {

    float helpVar = fabs(NormalizeMe->x) + fabs(NormalizeMe->y);
    NormalizeMe->x /= helpVar;
    NormalizeMe->y /= helpVar;
    }
}

sf::Vector2f ClCrowd::Seek(sf::Vector2f TargetPos, const sf::Vector2f & Destination, const sf::Vector2f & CurVelocity)
{
float Factor = 1;
    TargetPos.x -= Destination.x;
    TargetPos.y -= Destination.y;

        Factor = TargetPos.x*TargetPos.x + TargetPos.y *TargetPos.y;
        Factor /= MAXPPL*100;
        if (Factor > 1)
        {
            Factor = 1;
        }

    Vec2DNormalize(&TargetPos);
    TargetPos.x *=  Factor;
    TargetPos.y *=  Factor;

    return (-TargetPos - CurVelocity );
}
/*
sf::Vector2f ClCrowd::CenterForce(sf::Vector2f TargetPos, const sf::Vector2f & Destination, const sf::Vector2f & CurVelocity)
{
    TargetPos.x -= Destination.x;
    TargetPos.y -= Destination.y;

    //Vec2DNormalize(&TargetPos);

    return (-TargetPos - CurVelocity );
}*/


float ClCrowd::invert(float Max, float Current)
{
    return abs(Current - Max);
}

sf::Vector2f ClCrowd::DistanceForce(StrPeople* start,  int current)
{

    int n;

    sf::Vector2f delta;
    sf::Vector2f force(0,0);
    float helpVar;
    int NbCount = 0;

    for ( n = 0; n< MAXPPL; n++)
    {
        if ( n != current)
        {
            delta.x =   (start[current].position.x-start[n].position.x );
            delta.y =   (start[current].position.y-start[n].position.y );

            if (((delta.x*delta.x) + (delta.y * delta.y)) < 220)
            {
                helpVar = sqrt((delta.x*delta.x) + (delta.y * delta.y));
                Vec2DNormalize(&delta);
                helpVar = invert(sqrt(220),helpVar);

                force.x += delta.x *helpVar;
                force.y += delta.y *helpVar;
                NbCount++;
            }

        }
    }
    Vec2DNormalize(&force);
    if (NbCount <= 1)
    {
        return sf::Vector2f (0,0);
    }
    return -force;
}

