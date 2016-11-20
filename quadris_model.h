#ifndef _QUADRIS_MODEL_H_
#define _QUADRIS_MODEL_H_
#include <string>
#include <iostream>
#include "block.h"
#include "textdisplay.h"

class QuadrisModel {
public:
  QuadrisModel();
  void down();
  void right();
  void left();
  void drop();
  void clockwise();
  void cclockwise();
  void levelUp();
  void levelDown();
  bool isOver();

private:
  void clearRow();
  std::vector<Block> blocks;
  int level;
  static int high_score;
  int score;
  int seed;
  std::string sequence_file;
  Block current_block;
  void nextBlock();
  TextDisplay td;

  friend std::ostream &operator<<(std::ostream &out, const QuadrisModel &model);
};

#endif
