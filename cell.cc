#include "cell.h"

Cell::Cell(int x, int y, BlockType type) x(x), y(y), type(type) {}

Info Cell::getInfo() {
  return Info(x, y, type);
}

void Cell::down() {
  y++;
}

void Cell::left() {
  x--;
}

void Cell::right() {
  x++;
}
