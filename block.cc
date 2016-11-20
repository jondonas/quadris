#include "block.h"
#include <iostream>
using namespace std;

Block::Block(BlockType type) {
  if (type == BlockType::TBlock) {
    cells.push_back(Cell(0,0, type));
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

void Block::print() {
  for(auto cell : cells) {
    Info info = cell.getInfo;
    cout << "There is a cell at x: " << info.x << "y: " << info.y << endl;
  }
}
