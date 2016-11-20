#include "quadris_model.h"

QuadrisModel::QuadrisModel() {
  score = 0;
  seed = 0;
  level = 0;
  high_score = 0;
  sequence_file = "yo mama";
  nextBlock();
}

void QuadrisModel::down() {
  currentBlock.down();
  currentBlock.print();
}

void QuadrisModel::right() {
  currentBlock.right();
  currentBlock.print();
}

void QuadrisModel::left() {
  currentBlock.left();
  currentBlock.print();
}

void QuadrisModel::drop() {

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
  current_block = Block.new(BlockType::TBlock);
}
