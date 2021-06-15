#include <iostream>
#include "ui.h"
#include "fractal.h"

static constexpr int WIDTH = 1000;
static constexpr int HEIGHT = 600;

int main(){

    UI* ui = new UI(WIDTH, HEIGHT);
    ui->printInstructions();
    ui->run();

    return 0;
}
