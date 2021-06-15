#include "ui.h"

UI::UI(int width_, int height_){
    width = width_;
    height = height_;
    updated = true;

    julia = new Fractal(width, height, 250);
    moveX = 0.0;
    moveY = 0.0;
    zoom = 1.0;
}

void UI::run(){
    sf::RenderWindow window(sf::VideoMode(width, height), "Fractal");
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    window.setFramerateLimit(0);
    image.create(width, height, sf::Color(0, 0, 0));

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    updated = true;
                    handleKeyPress(event);
                default:
                    break;
            }
        }

        if(updated){
            julia->update(zoom, moveX, moveY, image);
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            updated = false;
        }

        window.draw(sprite);
        window.display();
    }
}

void UI::handleKeyPress(sf::Event event) {


    switch(event.key.code) {
        case sf::Keyboard::I:
            zoom /= 0.95;
            break;
        case sf::Keyboard::O:
            zoom *= 0.95;
            break;
        case sf::Keyboard::Up:
            moveY -= 0.35 * 1 / zoom;
            break;
        case sf::Keyboard::Down:
            moveY += 0.35 * 1 / zoom;
            break;
        case sf::Keyboard::Left:
            moveX -= 0.35 * 1 / zoom;
            break;
        case sf::Keyboard::Right:
            moveX += 0.35 * 1 / zoom;
            break;
        case sf::Keyboard::K:
            julia->setIterations(julia->getIterations() + 20);
            break;
        case sf::Keyboard::L:
            if(julia->getIterations() > 20) julia->setIterations(julia->getIterations() - 20);
            break;
        case sf::Keyboard::W:
            julia->setCIM(julia->getCIM() + 0.0005);
            break;
        case sf::Keyboard::S:
            julia->setCIM(julia->getCIM() - 0.0005);
            break;
        case sf::Keyboard::A:
            julia->setCRE(julia->getCRE() + 0.0005);
            break;
        case sf::Keyboard::D:
            julia->setCRE(julia->getCRE() - 0.0005);
            break;
        default:
            updated = false;
            break;
    }
}

void UI::printInstructions() {
    std::cout << "-------------------------------------------------\n"
                 "| STRZAŁKI | Poruszanie się góra-dół-lewo-prawo |\n"
                 "-------------------------------------------------\n"
                 "|    I     |          Przybliżenie              |\n"
                 "-------------------------------------------------\n"
                 "|    O     |           Oddalenie                |\n"
                 "-------------------------------------------------\n"
                 "|    K     |       Zwiększenie iteracji         |\n"
                 "-------------------------------------------------\n"
                 "|    L     |       Zmniejszenie iteracji        |\n"
                 "-------------------------------------------------\n"
                 "|  W / S   |        cImaginary ++ / --          |\n"
                 "-------------------------------------------------\n"
                 "|  A / D   |           cReal ++ / --            |\n"
                 "-------------------------------------------------\n" << std::endl;

}