#include "cell.h"

Cell::Cell(int x, int y, BlockType type): x{x}, y{y}, type{type} {}

Info Cell::getInfo() const{
  return {x, y, type};
}

void Cell::setCoords(int xx, int yy) {
  x = xx;
  y = yy;
}

void Cell::changeType(BlockType t) {
  type = t;
}
