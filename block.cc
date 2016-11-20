#include "block.h"
#include "info.h"
#include "block_type.h"
#include <iostream>
#include <vector>
using namespace std;

Block::Block(BlockType type, TextDisplay *td): td{td} {
  if (type == BlockType::TBlock) {
    init(cells, type, td, {{0,0},{1,0},{2,0},{1,1}});
  } else if (type == BlockType::IBlock) {

  } else if (type == BlockType::JBlock) {

  } else if (type == BlockType::LBlock) {

  } else if (type == BlockType::OBlock) {

  } else if (type == BlockType::SBlock) {

  } else if (type == BlockType::ZBlock) {

  }
}

void init(vector<Cell> &cells, BlockType type, TextDisplay *td,
vector<vector<int>> coords) {
  for (auto coord: coords) {
    Cell cell = Cell(coord[0], coord[1], type);
    cell.attach(td);
    cells.push_back(cell);
  }
}

vector<Cell> &Block::positions() {
  return cells;
}

void Block::down() {
  shift(cells, 0, 1);
}

void Block::left() {
  shift(cells, -1, 0);
}

void Block::right() {
  shift(cells, 1, 0);
}

void Block::clockwise() {
}

void Block::cclockwise() {
}

void clear(vector<Cell> &cells) {
  for (auto &cell: cells)
    cell.notifyObservers(true);
}

void draw(vector<Cell> &cells) {
  for (auto &cell: cells)
    cell.notifyObservers(false);
}

void shift(vector<Cell> &cells, int rightBy, int downBy) {
  clear(cells);
  for (auto &cell: cells) {
    Info info = cell.getInfo();
    cell.setCoords(info.x + rightBy, info.y + downBy);
  }
  draw(cells);
}
