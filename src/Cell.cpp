#include "Cell.h"
#include "Grid.h"

namespace gol {

Cell::Cell(unsigned int x, unsigned int y, Grid *grid, Color color, bool alive)
    : x(x), y(y), grid(grid), color(color), alive(alive), updated(true) {}

unsigned int Cell::getX() const { return x; }

unsigned int Cell::getY() const { return y; }

Grid *Cell::getGrid() const { return grid; }

Color Cell::getColor() const { return color; }

void Cell::setColor(Color color) { Cell::color = color; }

bool Cell::isAlive() const { return alive; }

void Cell::setAlive(bool alive) { Cell::alive = alive; }

Cell **Cell::getNeighbors() const { return neighbors; }

void Cell::setNeighbors() {
  neighbors = new Cell *[8];
  if (x > 0) {
    neighbors[0] = &grid->at(x - 1, y);
    if (y > 0) {
      neighbors[1] = &grid->at(x - 1, y - 1);
    }
    if (y < grid->getHeight() - 1) {
      neighbors[2] = &grid->at(x - 1, y + 1);
    }
  } else {
    neighbors[0] = nullptr;
    neighbors[1] = nullptr;
    neighbors[2] = nullptr;
  }
  if (x < grid->getWidth() - 1) {
    neighbors[3] = &grid->at(x + 1, y);
    if (y > 0) {
      neighbors[4] = &grid->at(x + 1, y - 1);
    }
    if (y < grid->getHeight() - 1) {
      neighbors[5] = &grid->at(x + 1, y + 1);
    }
  } else {
    neighbors[3] = nullptr;
    neighbors[4] = nullptr;
    neighbors[5] = nullptr;
  }
  if (y > 0) {
    neighbors[6] = &grid->at(x, y - 1);
  } else {
    neighbors[6] = nullptr;
  }
  if (y < grid->getHeight() - 1) {
    neighbors[7] = &grid->at(x, y + 1);
  } else {
    neighbors[7] = nullptr;
  }
}

Cell::Cell(const Cell &copy) { *this = copy; }

Cell &Cell::operator=(const Cell &copy) {
  x = copy.x;
  y = copy.y;
  color = copy.color;
  alive = copy.alive;
  grid = nullptr;
  neighbors = nullptr;
  return *this;
}

void Cell::setGrid(Grid *grid) { Cell::grid = grid; }

void Cell::update() {
  float red = 0, green = 0, blue = 0, allies = 0, enemies = 0;
  Color winner = Color::Red;
  for (int i = 0; i < 8; i++) {
    if (neighbors[i] != nullptr && neighbors[i]->alive) {
      if (neighbors[i]->color == Color::Red) {
        red++;
      } else if (neighbors[i]->color == Color::Green) {
        green++;
      } else if (neighbors[i]->color == Color::Blue) {
        blue++;
      }
    }
  }

  if (red > blue * 2 && red > green / 3) {
    winner = Color::Red;
    allies = red;
    enemies = blue * 2 + green / 3;
  } else if (green > red * 2 && green > blue / 3) {
    winner = Color::Green;
    allies = green;
    enemies = red * 2 + blue / 3;
  } else if (blue > green * 2 && blue > red / 3) {
    winner = Color::Blue;
    allies = blue;
    enemies = green * 2 + red / 3;
  }

  if (allies > 0 || enemies > 0) {
    if (!alive && allies > enemies) {
      alive = true;
      color = winner;
      updated = true;
    } else if (alive && winner != color) {
      alive = false;
      updated = true;
    } else {
      updated = false;
    }
  } else {
    alive = false;
  }
}

bool Cell::isUpdated() const { return updated; }
} // namespace gol