#ifndef SIMULATIONAREA_HPP_INCLUDED
#define SIMULATIONAREA_HPP_INCLUDED

#include "SFML_Widget.hpp"
#include <gtkmm.h>
#include "../Simulator/Area.hpp"


using namespace std;

class SimulationArea : public SFML_Widget
{
private:
    ClArea *Area;
    Gtk::Box *ObjectBox;
    int selectedID;
    Gtk::SpinButton *SizeX;
    Gtk::SpinButton *SizeY;
    Gtk::SpinButton *Rot;
    Gtk::SpinButton *pAreaSizeX;
    Gtk::SpinButton *pAreaSizeY;
    bool boxChecked;
    vector<Gtk::CheckButton*> CheckButt;

    void animate();
    void draw();
    void resize();
    sf::Color bgColor;
public:
    SimulationArea(Gtk::ScrolledWindow& AreaWin, Gtk::Box& ObjectBox, Gtk::SpinButton *SizeX,
                   Gtk::SpinButton *SizeY, Gtk::SpinButton *Rot,  Gtk::SpinButton *pAreaSizeX,
                   Gtk::SpinButton *pAreaSizeY);
    void clearArea();
    void setObject(enum staticObjects object, sf::Vector2f position, sf::Vector2f size, float rotation);
    void setChecked();
    ClArea *getArea();
    void insertCheck(Gtk::CheckButton *check);
    void box_clicked();
    void setBgColor(sf::Color pColor){bgColor = pColor;};
};

#endif // SIMULATIONAREA_HPP_INCLUDED
