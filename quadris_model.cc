#include "quadris_model.h"
#include <iostream>

// todo: make td a smart pointer
QuadrisModel::QuadrisModel(): td{TextDisplay()}, 
current_block{Block(BlockType::TBlock, &td)} {
  score = 0;
  seed = 0;
  level = 0;
  //high_score = 0;
  sequence_file = "yo mama";
  //nextBlock();
}

void QuadrisModel::down() {
  current_block.down();
}

void QuadrisModel::right() {
  current_block.right();
}

void QuadrisModel::left() {
  current_block.left();
}

void QuadrisModel::drop() {

}

void QuadrisModel::clockwise() {
  current_block.clockwise();
}

void QuadrisModel::cclockwise() {
  current_block.clockwise();
}

void QuadrisModel::levelUp() {
  ++level;
}

void QuadrisModel::levelDown() {
  --level;
}

bool QuadrisModel::isOver() {
  false;
}

void QuadrisModel::clearRow() {

}

void nextBlock() {
  //current_block = Block(BlockType::TBlock);
}

std::ostream &operator<<(std::ostream &out, const QuadrisModel &model) {
  std::cout << model.td;
  return out;
}
