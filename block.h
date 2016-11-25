#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include <memory>
#include "block_type.h"
#include "cell.h"
#include "textdisplay.h"
using namespace std;

class Block {
public:
  Block(BlockType type, shared_ptr<TextDisplay>, int);
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
  bool isEmpty() const;
  int getLevel() const;

private:
  BlockType type;
  int level;
  std::vector<Cell> cells;
  std::shared_ptr<TextDisplay> td;
  void init(vector<vector<int>>);
  void clear();
  void shift(int, int);
};

#endif
