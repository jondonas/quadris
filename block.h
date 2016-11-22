#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include "block_type.h"
#include "cell.h"
#include "textdisplay.h"
using namespace std;

class Block {
public:
  Block(BlockType type, TextDisplay *, bool heavy = false);
  std::vector<Cell> &positions();
  void down();
  void left();
  void right();
  void clockwise();
  void cclockwise();

private:
  std::vector<Cell> cells;
  TextDisplay *td;
  void init(BlockType, vector<vector<int>>);
  void clear();
  void shift(int, int);
  bool heavy;
  vector<int> maxMin() const;
};

#endif
