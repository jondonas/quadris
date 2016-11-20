#include "quadris_model.h"
#include <iostream>

QuadrisModel::QuadrisModel(): current_block{Block(BlockType::TBlock)} {
  score = 0;
  seed = 0;
  level = 0;
  //high_score = 0;
  sequence_file = "yo mama";
  //nextBlock();
}

void QuadrisModel::down() {
  current_block.down();
  current_block.print();
}

void QuadrisModel::right() {
  current_block.right();
  current_block.print();
}

void QuadrisModel::left() {
  current_block.left();
  current_block.print();
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
