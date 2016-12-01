#ifndef _CELL_H_
#define _CELL_H_
#include "info.h"
#include "block_type.h"
#include "textdisplay.h"
#include "subject.h"

class Cell: public Subject {
public:
  Cell(int, int, BlockType);
  Info getInfo() const override;
  void setCoords(int, int);
  void changeType(BlockType);
private:
  int x;
  int y;
  BlockType type;
};

#endif
