#ifndef _CELL_H_
#define _CELL_H_
#include "info.h"
#include "block_type.h"

class Cell {
public:
  Cell(int, int, BlockType);
  Info getInfo();
  void down();
  void left();
  void right();
private:
  int x;
  int y;
  BlockType type;
};

#endif
