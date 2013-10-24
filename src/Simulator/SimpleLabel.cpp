#include "../../include/Simulator/SimpleLabel.hpp"
#include <sstream>

ClSimpleLabel::ClSimpleLabel(const sf::Vector2f &position, const sf::Vector2f &labelSize, const sf::String &labelText, const sf::Font &font, int *pNumber)
{
    this->position = position;
    this->labelSize = labelSize;
    this->labelText = labelText;
    this->pNumber = pNumber;

    textSpace.setPosition(position);
    textSpace.setSize(labelSize);

    spaceColor.r = spaceColor.g = spaceColor.b = 255;
    spaceColor.a = 50;
    textSpace.setFillColor(spaceColor);

    text.setPosition(position.x+ labelSize.x/4,position.y);

    title = labelText;
    text.setColor(sf::Color::Red);
    text.setFont(font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);

}


void ClSimpleLabel::draw(sf::RenderWindow& window)
{
    std::stringstream number_ss;
    number_ss << *pNumber;
    number = number_ss.str();

    text.setString(title + "\n" + number);

    window.draw(textSpace);
    window.draw(text);
}
