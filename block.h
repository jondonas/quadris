#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include "block_type.h"
#include "cell.h"

class Block {
public:
  Block(BlockType type);
  std::vector<Cell> &positions();
  void down();
  void left();
  void right();
  void clockwise();
  void cclockwise();
  void print();

private:
  std::vector<Cell> cells;
};

#endif
