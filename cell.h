#ifndef _CELL_H_
#define _CELL_H_
#include "info.h"
#include "block_type.h"
#include "textdisplay.h"

class Cell {
public:
  Cell(int, int, BlockType, TextDisplay *td);
  Info getInfo();
  void setCoords(int, int);
private:
  TextDisplay *td;
  int x;
  int y;
  BlockType type;
};

#endif
