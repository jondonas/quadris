#include "cell.h"
#include <iostream>

Cell::Cell(int x, int y, BlockType type, TextDisplay *td): x{x}, y{y}, type{type}, td{td} {
  std::cout << td << std::endl;
}

Info Cell::getInfo() {
  return {x, y, type};
}

void Cell::setCoords(int xx, int yy) {
  x = xx;
  y = yy;
  td->notify(getInfo());
}
