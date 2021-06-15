#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <thread>
#include <ctime>
#include "fractal.h"

#ifndef PROJEKT_UI_H
#define PROJEKT_UI_H

class UI {
public:
    UI(int, int);
    void printInstructions();
    void run();

private:
    void handleEvents(sf::Event);
    void handleKeyPress(sf::Event);

    sf::RenderWindow* window;
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    bool updated;
    int width, height;

    Fractal* julia;
    double zoom;
    double moveX;
    double moveY;
};


#endif
