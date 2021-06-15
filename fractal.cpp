#include "fractal.h"
#include <thread>


Fractal::Fractal(int width_, int height_, int iterations) {
    width = width_;
    height = height_;
    maxIterations = iterations;
    cReal = -0.7;
    cImaginary = 0.27015;
}


void Fractal::update(double zoom, double moveX, double moveY, sf::Image& image) const{
    const int step = height / 16;
    std::vector<std::thread> threads;
    for (int i = 0; i < width; i += step) {
        threads.push_back(std::thread(&Fractal::draw, *this, zoom, moveX, moveY, std::ref(image), i, std::min(i + step, (int)width)));
    }
    for (auto &t : threads) {
        t.join();
    }
}

int Fractal::calculate(double nextReal, double nextImaginary) {
    int i;
    for(i = 0; i < maxIterations; i++)
    {
        double oldReal = nextReal;
        double oldImaginary = nextImaginary;

        nextReal = oldReal * oldReal - oldImaginary * oldImaginary + cReal;
        nextImaginary = 2 * oldReal * oldImaginary + cImaginary;

        if((nextReal * nextReal + nextImaginary * nextImaginary) > 4) break;
    }

    return i;
}

void Fractal::draw(double zoom_, double moveX, double moveY, sf::Image& image, int start, int end){
    double nextReal, nextImaginary;
    sf::Color color;

    for(int y = 0; y < height; y++)
        for(int x = start; x < end; x++)
        {
            nextReal = 1.5 * (x - width / 2) / (0.5 * zoom_ * width) + moveX;
            nextImaginary = (y - height / 2) / (0.5 * zoom_ * height) + moveY;

            int iter = calculate(nextReal, nextImaginary);
            color = getHSVColor(iter % 256, 255, 255 * (iter < maxIterations));
            image.setPixel(x, y, color);
        }
}

sf::Color Fractal::getHSVColor(int hue, float sat, float val){
    hue %= 360;
    while (hue<0) hue += 360;

    if (sat<0.f) sat = 0.f;
    if (sat>1.f) sat = 1.f;

    if (val<0.f) val = 0.f;
    if (val>1.f) val = 1.f;

    int h = hue / 60;
    float f = float(hue) / 60 - h;
    float p = val*(1.f - sat);
    float q = val*(1.f - sat*f);
    float t = val*(1.f - sat*(1 - f));

    switch (h)
    {
        default:
        case 0:
        case 6: return sf::Color(val * 255, t * 255, p * 255);
        case 1: return sf::Color(q * 255, val * 255, p * 255);
        case 2: return sf::Color(p * 255, val * 255, t * 255);
        case 3: return sf::Color(p * 255, q * 255, val * 255);
        case 4: return sf::Color(t * 255, p * 255, val * 255);
        case 5: return sf::Color(val * 255, p * 255, q * 255);
    }
}
