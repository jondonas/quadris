#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <vector>
#include <memory>
#include "block_type.h"
#include "cell.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;

class Block {
public:
  Block(BlockType type, shared_ptr<TextDisplay>, shared_ptr<GraphicsDisplay>, int, int offset_x = 0, int offset_y = 0);
  std::vector<Cell> positions();
  void down();
  void left();
  void right();
  void clockwise();
  void cclockwise();
  int colsOccupied(int);
  void remove(int);
  void dropAbove(int); 
  void clear();
  void draw() const;
  vector<int> maxMin() const;
  bool isHeavy() const;
  bool isEmpty() const;
  int getLevel() const;
  int getX() const;
  int getY() const;
  BlockType getType() const;
  void changeType(BlockType);

private:
  BlockType type;
  int level;
  int x;
  int y;
  std::vector<Cell> cells;
  std::shared_ptr<TextDisplay> td;
  std::shared_ptr<GraphicsDisplay> gd;
  void init(vector<vector<int>>, int offset_x = 0, int offset_y = 0);
  void shift(int, int);
};

#endif
