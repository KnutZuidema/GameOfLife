#include "Grid.h"
#include "Cell.h"

namespace gol {

unsigned int Grid::getWidth() const { return width; }

unsigned int Grid::getHeight() const { return height; }

unsigned int Grid::getSize() const { return size; }

Grid::Grid(unsigned int width, unsigned int height, Color cellColor(void),
           bool cellAlive(unsigned int), unsigned int spawn_chance)
    : width(width), height(height), size(width * height) {
  grid = new Cell *[size];
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      grid[x * height + y] =
          new Cell(x, y, this, cellColor(), cellAlive(spawn_chance));
    }
  }
  for (unsigned int i = 0; i < size; i++) {
    grid[i]->setNeighbors();
  }
}

Cell &Grid::operator()(unsigned int x, unsigned int y) const {
  return at(x, y);
}

Cell &Grid::at(unsigned int x, unsigned int y) const {
  return *grid[x * height + y];
}

Cell *Grid::begin() const { return grid[0]; }

Cell *Grid::end() const { return grid[size]; }

Cell &Grid::operator[](unsigned int x) const { return *grid[x]; }

Grid::Grid(const Grid &copy) { *this = copy; }

Grid &Grid::operator=(const Grid &copy) {
  width = copy.width;
  height = copy.height;
  size = copy.size;
  grid = new Cell *[size];
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      grid[x * height + y] = new Cell(*copy.grid[x * height + y]);
      grid[x * height + y]->setGrid(this);
    }
  }
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      grid[x * height + y]->setNeighbors();
    }
  }

  return *this;
}
} // namespace gol