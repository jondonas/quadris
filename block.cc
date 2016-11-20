#include "block.h"
using namespace std;

Block::Block(BlockType type) {
  if (type == BlockType::TBlock) {

  } else if (type == BlockType::IBlock) {

  } else if (type == BlockType::JBlock) {

  } else if (type == BlockType::LBlock) {

  } else if (type == BlockType::OBlock) {

  } else if (type == BlockType::SBlock) {

  } else if (type == BlockType::ZBlock) {

  }
}

vector<Cell> &Block::positions() {
  return cells;
}

void Block::down() {
  for(auto cell : cells) {
    cell.down();
  }
}

void Block::left() {
  for(auto cell : cells) {
    cell.left();
  }
}

void Block::right() {
  for(auto cell : cells) {
    cell.right();
  }
}

void Block::clockwise() {
}

void Block::cclockwise() {
}
