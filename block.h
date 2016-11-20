#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>

class Block {
public:
  Block();
  std::vector<Cell> &positions();
  void down();
  void left();
  void right();
  void clockwise();
  void cclockwise();

private:
  std::vector<Cell> cells;
}

#endif
