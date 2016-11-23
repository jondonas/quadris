#include "block.h"
#include "info.h"
#include "block_type.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

Block::Block(BlockType type, TextDisplay *td): type{type}, td{td} {
  if (type == BlockType::TBlock) {
    init({{0,0},{1,0},{2,0},{1,1}});
  } else if (type == BlockType::IBlock) {
    init({{0,0},{1,0},{2,0},{3,0}});
  } else if (type == BlockType::JBlock) {
    init({{0,0},{0,1},{1,1},{2,1}});
  } else if (type == BlockType::LBlock) {
    init({{2,0},{0,1},{1,1},{2,1}});
  } else if (type == BlockType::OBlock) {
    init({{0,0},{0,1},{1,0},{1,1}});
  } else if (type == BlockType::SBlock) {
    init({{0,1},{1,1},{1,0},{2,0}});
  } else if (type == BlockType::ZBlock) {
    init({{0,0},{1,0},{1,1},{2,1}});
  }
}

void Block::init(vector<vector<int>> coords) {
  for (auto coord: coords) {
    Cell cell = Cell(coord[0], coord[1], type);
    cell.attach(td);
    cells.push_back(cell);
  }
}

vector<Cell> Block::positions() {
  return cells;
}

void Block::down() {
  shift(0, 1);
}

void Block::left() {
  shift(-1, 0);
}

void Block::right() {
  shift(1, 0);
}

void Block::clockwise() {
  clear();
  vector<int> vals = maxMin();
  for (auto &cell: cells) {
    Info info = cell.getInfo();
    cell.setCoords(info.x - (info.x - vals[3]) + (vals[2] - info.y),
                   info.y - (vals[1] - info.x) + (vals[2] - info.y));
    cell.notifyObservers(false);
  }
}

void Block::cclockwise() {
  clear();
  vector<int> vals = maxMin();
  for (auto &cell: cells) {
    Info info = cell.getInfo();
    cell.setCoords(info.x - (info.x - vals[3]) + (info.y - vals[0]),
                   info.y - (info.x - vals[3]) + (vals[2] - info.y));
    cell.notifyObservers(false);
  }
}

void Block::clear() {
  for (auto &cell: cells)
    cell.notifyObservers(true);
}

void Block::shift(int rightBy, int downBy) {
  clear();
  for (auto &cell: cells) {
    Info info = cell.getInfo();
    cell.setCoords(info.x + rightBy, info.y + downBy);
    cell.notifyObservers(false);
  }
}

// Returns the smallest y, largest x, largest y, smallest x of cells in the block
// needed for rotation calculations.
vector<int> Block::maxMin() const {
  vector<int> x_vals, y_vals;
  for (auto cell: cells) {
    x_vals.push_back(cell.getInfo().x);
    y_vals.push_back(cell.getInfo().y);
  }
  auto x_result = minmax_element(x_vals.begin(), x_vals.end());
  auto y_result = minmax_element(y_vals.begin(), y_vals.end());

  return {*y_result.first, *x_result.second, *y_result.second, *x_result.first};
}

void Block::draw() const {
  for (auto cell: cells)
    cell.notifyObservers(false);
}
