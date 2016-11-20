#ifndef _CELL_H_
#define _CELL_H_
#include "info.h"

class Cell {
public:
  Cell();
  Info getInfo();
  void down();
  void left();
  void right();
private:
  int x;
  int y;
}

#endif
