#ifndef _QUADRIS_MODEL_H_
#define _QUADRIS_MODEL_H_
#include "block.h"

class QuadrisModel {
public:
  QuadrisModel();
  void down();
  void right();
  void left();
  void drop();
  void levelUp();
  void levelDown();
  bool isOver();

private:
  void clearRow();
  std::vector<Block&> blocks;
  int level;
  static int high_score;
  int score;
  int seed;
  std::string sequence_file;
}

#endif
