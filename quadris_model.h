#ifndef _QUADRIS_MODEL_H_
#define _QUADRIS_MODEL_H_
#include <string>
#include <iostream>
#include <fstream>
#include "block.h"
#include "textdisplay.h"

class QuadrisModel {
public:
  QuadrisModel();
  void down(int m);
  void right(int m);
  void left(int m);
  void drop(int m);
  void clockwise(int m);
  void cclockwise(int m);
  void levelUp(int m);
  void levelDown(int m);
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
  std::ifstream file_in;
  void nextBlock();
  TextDisplay td;

  friend std::ostream &operator<<(std::ostream &out, const QuadrisModel &model);
};

#endif
