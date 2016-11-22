#include "block.h"
#include "info.h"
#include "block_type.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

Block::Block(BlockType type, TextDisplay *td, bool heavy): td{td}, heavy(heavy) {
  if (type == BlockType::TBlock) {
    init(type, {{0,0},{1,0},{2,0},{1,1}});
    cout << "would have made an TBlock" << endl;
  } else if (type == BlockType::IBlock) {
    cout << "would have made an IBlock" << endl;
  } else if (type == BlockType::JBlock) {
    cout << "would have made an JBlock" << endl;
  } else if (type == BlockType::LBlock) {
    cout << "would have made an LBlock" << endl;
  } else if (type == BlockType::OBlock) {
    cout << "would have made an OBlock" << endl;
  } else if (type == BlockType::SBlock) {
    cout << "would have made an SBlock" << endl;
  } else if (type == BlockType::ZBlock) {
    cout << "would have made an ZBlock" << endl;
  }
}

void Block::init(BlockType type, vector<vector<int>> coords) {
  for (auto coord: coords) {
    Cell cell = Cell(coord[0], coord[1], type);
    cell.attach(td);
    // this should draw the block on creation but I get a segfault and
    // can't find the reason yet!
    //cell.notifyObservers(false);
    cells.push_back(cell);
  }
}

vector<Cell> &Block::positions() {
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
// Will probably make this public later so the model can use this for bounds checking
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
