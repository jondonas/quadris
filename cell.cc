#include "cell.h"
#include <iostream>

Cell::Cell(int x, int y, BlockType type): x(x), y(y), type(type) {}

Info Cell::getInfo() {
  return {x, y, type};
}

void Cell::down() {
  ++y;
}

void Cell::left() {
  --x;
  std::cout << "set: " << x << std::endl;
}

void Cell::right() {
  ++x;
}
