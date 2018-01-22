#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Cell.h"
#include "Grid.h"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

bool rand_bool(unsigned int spawn_chance){
    static std::mt19937 rand((unsigned int)time(nullptr));

    return rand() % 1000 < spawn_chance;
}

gol::Color rand_color(){
    static std::mt19937 rand((unsigned int)time(nullptr));

    int x = rand() % 3;
    if(x == 0){
        return gol::Color::Red;
    }else if(x == 1){
        return gol::Color::Green;
    }else{
        return gol::Color::Blue;
    }
}

sf::Color convert_color(gol::Color c) {
    if (c == gol::Color::Red) {
        return sf::Color::Red;
    } else if (c == gol::Color::Green) {
        return sf::Color::Green;
    } else {
        return sf::Color::Blue;
    }
}

int main(int argc, const char* argv[]) {
    unsigned int width = 400, height = 300, spawn_chance = 100, cell_size = 3, border_size = 30, frame_rate = 30;

    po::options_description desc("Usage");
    desc.add_options()
            ("help", "produce this help message")
            ("width,w", po::value<unsigned int>(&width)->default_value(width), "uint, amount of cells horizontally")
            ("height,h", po::value<unsigned int>(&height)->default_value(height), "uint, amount of cells vertically")
            ("spawn_chance,s", po::value<unsigned int>(&spawn_chance)->default_value(spawn_chance),
             "uint, chance of a living cell per 1000")
            ("cell_size,c", po::value<unsigned int>(&cell_size)->default_value(cell_size),
             "uint, size of the individual cells in pixels")
            ("border_size,b", po::value<unsigned int>(&border_size)->default_value(border_size),
             "uint, size of the border in pixels")
            ("frame_rate,f", po::value<unsigned int>(&frame_rate)->default_value(frame_rate), "uint, max frame rate");

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }catch (...){
        std::cout << "Invalid parameters\n" << desc << '\n';
        return 1;
    }

    if(vm.count("help")){
        std::cout << desc << '\n';
        return 1;
    }

    gol::Grid grid(width, height, rand_color, rand_bool, spawn_chance);

    sf::RenderWindow window(sf::VideoMode(border_size*2 + width * cell_size, border_size*2 + height * cell_size),
                            "Game of Life");

    sf::RenderTexture renderTexture;
    renderTexture.create(width*cell_size, height*cell_size);

    sf::Sprite sprite(renderTexture.getTexture());
    sprite.setPosition(border_size, border_size);

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");

    sf::Text fps;
    fps.setFont(font);
    fps.setPosition(5, 5);
    fps.setCharacterSize(13);

    sf::RectangleShape* cells = new sf::RectangleShape[grid.getSize()];
    for (unsigned int i = 0; i < grid.getSize(); i++) {
        cells[i] = *new sf::RectangleShape(sf::Vector2f(cell_size, cell_size));
        cells[i].setPosition(cell_size * grid[i].getX(), cell_size * grid[i].getY());
    }

    sf::Clock clock;
    clock.restart();

    sf::Event e{};
    window.setFramerateLimit(frame_rate);
    while (window.isOpen()) {
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        for (unsigned int i = 0; i < grid.getSize(); i++) {
            if(grid[i].isUpdated()) {
                if (grid[i].isAlive()) {
                    cells[i].setFillColor(convert_color(grid[i].getColor()));
                    renderTexture.draw(cells[i]);
                } else {
                    cells[i].setFillColor(sf::Color::White);
                    renderTexture.draw(cells[i]);
                }
            }
        }

        sprite.setTexture(renderTexture.getTexture());

        window.draw(sprite);

        for (unsigned int i = 0; i < grid.getSize(); i++) {
            grid[i].update();
        }

        fps.setString(std::to_string(1000/clock.restart().asMilliseconds()) + " FPS");

        window.draw(fps);

        window.display();
    }
}
