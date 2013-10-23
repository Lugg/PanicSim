
#include "../../include/Simulator/SimpleSimulationMenu.hpp"


ClSimpleSimulationMenu::ClSimpleSimulationMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize)
    {
        this->myState = myState;
        this->pFont = pFont;
        this->screenSize = screenSize;
        texture.loadFromFile("pictures/ButtonSet1.png");
        createMenu();
    }

    void ClSimpleSimulationMenu::draw(sf::RenderWindow &window) const
    {
        for(int n = 0; n < ButtonVector.size();n++)
        {
            ButtonVector[n]->draw(window);
        }
    }

    enum GameStates ClSimpleSimulationMenu::execute(enum Buttons btn) const
    {
        switch(btn)
        {
        case(HEATMAP):
            {
                ClHeatMap::toggleDraw();
            }break;
        case(PLAY):
            {
                ClSimulation::updateSpeed(false, true, false);
            }break;
        case(FASTFORWARD):
            {
                ClSimulation::updateSpeed(false, false, true);
            }break;
        case(PAUSE):
            {
                ClSimulation::updateSpeed(true,false,false);
            }break;
        case(BOMB):
            {
                ClThreatManager::buttonPressed(true, false);
            }break;
        case(FIRE):
            {
               // ClThreatManager::buttonPressed(false, true);
            }break;
        }
        return SIMULATION;
    }

    //virtual void execute(enum Buttons btn) const = 0;
    enum GameStates ClSimpleSimulationMenu::update(sf::RenderWindow &window) const
    {
        sf::Event event;
        window.pollEvent(event);
        if( event.type == sf::Event::MouseButtonReleased)
        {
        for (unsigned int n = 0;n<ButtonVector.size();n++)
        {
            if (ButtonVector[n]->isPressed(window))
            {
                execute(ButtonVector[n]->getButtonType());
            }
        }
        }
        return SIMULATION;
    }
   // private:
    void ClSimpleSimulationMenu::createMenu()
    {
        ClSimpleButton *pAddMe;
        int id = 0;
        sf::Vector2f ButtonSize;
        ButtonSize.x = texture.getSize().x;
        ButtonSize.y = texture.getSize().y;
        ButtonSize.x /=2;
        ButtonSize.y /=3;
        sf::Vector2f Position;
        Position.x = ButtonSize.x / 2;
        Position.y = this->screenSize.y - ButtonSize.y;
        float scale = 0.35f;
        // add STOP Button
        id++;
        pAddMe = new ClSimpleButton(id, STOP,2, SIMULATION, texture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add PLAY Button
         Position.x+=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, PLAY,3, SIMULATION, texture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add FASTFORWARD Button
        Position.x+=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, FASTFORWARD,4, SIMULATION, texture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);

        // Add down right Buttons
        Position.x = screenSize.x;
        Position.y = screenSize.y;

        Position.y -= ButtonSize.y;
        Position.x -= 0.25 *ButtonSize.x;

        // add HEATMAP Button
         Position.x-=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, HEATMAP,0, SIMULATION, texture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add BOMB Button
        Position.x-=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, BOMB,1, SIMULATION, texture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add FIRE Button
        Position.x-=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, FIRE,5, SIMULATION, texture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
    }
