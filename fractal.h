#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>

#ifndef PROJEKT_FRACTAL_H
#define PROJEKT_FRACTAL_H

class Fractal{
public:
    Fractal(int, int, int);

    void update(double, double, double, sf::Image&) const;

    void setIterations(int x){ maxIterations = x; }
    int getIterations(){ return maxIterations; }

    void setCRE(double c){ cReal = c; }
    double getCRE(){ return cReal; }
    void setCIM(double c){ cImaginary = c; }
    double getCIM(){ return cImaginary; }

private:
    void draw(double, double, double, sf::Image&, int, int);
    int calculate(double, double);

    sf::Color getHSVColor(int, float, float);

    int width;
    int height;
    int maxIterations;

    double cReal;
    double cImaginary;
};



#endif
