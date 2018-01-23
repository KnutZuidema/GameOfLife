#ifndef GAMEOFLIFE_CELL_H
#define GAMEOFLIFE_CELL_H

namespace gol {
    class Grid; //Mock-Class to avoid endless compilation loop

    enum class Color{
        Red,
        Green,
        Blue
    };

    class Cell {
    private:
        unsigned int x, y;
        Grid* grid;
        Color color;
        bool alive, updated;
        Cell** neighbors;

    public:
        Cell() = default;

        Cell(unsigned int x, unsigned int y, Grid *grid, Color color, bool alive);

        Cell(const Cell& copy);

        Cell& operator=(const Cell& copy);

        unsigned int getX() const;

        unsigned int getY() const;

        Grid *getGrid() const;

        void setGrid(Grid *grid);

        Color getColor() const;

        Cell **getNeighbors() const;

        void setNeighbors();

        void setColor(Color color);

        bool isAlive() const;

        void setAlive(bool alive);

        bool isUpdated() const;

        void update();
    };
}

#endif //GAMEOFLIFE_CELL_H
