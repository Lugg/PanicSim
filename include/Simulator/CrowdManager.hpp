#ifndef CROWDMANAGER_HPP
#define CROWDMANAGER_HPP

#include "Area.hpp"
#include "Crowd.hpp"
#include "HeatMap.hpp"
#include "PathFinder.hpp"
#include <vector>

class ClCrowdManager
{
    public:
        ClCrowdManager(ClArea *pArea, const sf::Vector2i &ScreenSize);
        ~ClCrowdManager();

        void Update(float frameTime, sf::RenderWindow &window);
        void draw(sf::RenderWindow& window);
        void CreateCrowd(sf::Vector2f position, float radius, int people);

        // for lable showing the total ammount of people
        static int *getPeopleCount();
        static void addPeople(int Number);

    private:

        ClArea *pArea;
        ClHeatMap *pHeatMap;
        ClPathFinder *pPathFinder;
        std::vector<ClCrowd *> Crowds;

        static int peopleCount;
};

#endif // CROWDMANGER_HPP
