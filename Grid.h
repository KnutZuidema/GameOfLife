#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H

namespace gol {
    class Cell;
    enum class Color; //Mock-Classes to avoid endless compilation loop

    class Grid {
    private:
        unsigned int width, height, size;
        Cell** grid;

    public:
        Grid(unsigned int width, unsigned int height, Color cellColor(void), bool cellAlive(unsigned int),
             unsigned int spawn_chance);

        Grid(const Grid& copy);

        Cell& operator()(unsigned int x, unsigned int y) const;

        Cell& operator[](unsigned int x) const;

        Grid& operator=(const Grid& copy);

        Cell& at(unsigned int x, unsigned int y) const;

        Cell* begin() const;

        Cell* end() const;

        unsigned int getWidth() const;

        unsigned int getHeight() const;

        unsigned int getSize() const;
    };
}


#endif //GAMEOFLIFE_GRID_H
