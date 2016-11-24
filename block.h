#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include "block_type.h"
#include "cell.h"
#include "textdisplay.h"
using namespace std;

class Block {
public:
  Block(BlockType type, TextDisplay *, bool);
  std::vector<Cell> positions();
  void down();
  void left();
  void right();
  void clockwise();
  void cclockwise();
  int colsOccupied(int);
  void remove(int);
  void dropAbove(int); 
  void draw() const;
  vector<int> maxMin() const;
  bool isHeavy() const;

private:
  BlockType type;
  bool heavy;
  std::vector<Cell> cells;
  TextDisplay *td;
  void init(vector<vector<int>>);
  void clear();
  void shift(int, int);
};

#endif
