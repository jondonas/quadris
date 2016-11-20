#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include "block_type.h"
#include "cell.h"
#include "textdisplay.h"
//class TextDisplay;

class Block {
public:
  Block(BlockType type, TextDisplay *);
  std::vector<Cell> &positions();
  void down();
  void left();
  void right();
  void clockwise();
  void cclockwise();

private:
  std::vector<Cell> cells;
  TextDisplay *td;
};

#endif
