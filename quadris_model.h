#ifndef _QUADRIS_MODEL_H_
#define _QUADRIS_MODEL_H_
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include "block.h"
#include "info.h"
#include "textdisplay.h"

class QuadrisModel {
public:
  QuadrisModel(bool, unsigned, std::string, int);
  void down(int m);
  void right(int m);
  void left(int m);
  void drop(int m);
  void clockwise(int m);
  void cclockwise(int m);
  void levelUp(int m);
  void levelDown(int m);
  bool isOver();
  bool setSeqFile(std::string);
  void setRandom(bool);
  void swapType(BlockType);

private:
  void clearRows();
  std::vector<Block> blocks;
  std::vector<Info> positions;
  int level;
  static int high_score;
  int score;
  unsigned seed;
  bool block_random;
  bool seed_set;
  Block current_block;
  BlockType next_block;
  std::ifstream file_in;
  bool lost;
  void nextBlock();
  bool canDown();
  bool canRight();
  bool canLeft();
  bool canClock();
  bool canCclock();
  bool isOpen(int, int);
  bool canMove(int, int);
  void updatePositions();
  void updateScore(int);
  void clearBlocks();
  std::shared_ptr<TextDisplay> td;

  friend std::ostream &operator<<(std::ostream &out, const QuadrisModel &model);
};

#endif
