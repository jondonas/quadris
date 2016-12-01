#include "block.h"
#include "info.h"
#include "block_type.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

Block::Block(BlockType type, shared_ptr<TextDisplay> td, shared_ptr<GraphicsDisplay> gd, int level, int offset_x, int offset_y): type{type}, td{td}, gd{gd}, level{level} { 
  vector<vector<int>> coords;
  if (type == BlockType::TBlock) {
    coords = {{0,-1},{1,-1},{2,-1},{1,0}};
  } else if (type == BlockType::IBlock) {
    coords = {{0,0},{1,0},{2,0},{3,0}};
  } else if (type == BlockType::JBlock) {
    coords = {{0,-1},{1,-1},{2,-1},{2,0}};
  } else if (type == BlockType::LBlock) {
    coords = {{2,-1},{0,0},{1,0},{2,0}};
  } else if (type == BlockType::OBlock) {
    coords = {{0,-1},{0,0},{1,-1},{1,0}};
  } else if (type == BlockType::SBlock) {
    coords = {{0,0},{1,0},{1,-1},{2,-1}};
  } else if (type == BlockType::ZBlock) {
    coords = {{0,-1},{1,-1},{1,0},{2,0}};
  } else if (type == BlockType::SingleBlock) {
    coords = {{0, 0}};
  }
  x = offset_x;
  y = offset_y;
  init(coords, offset_x, offset_y);
}

void Block::init(vector<vector<int>> coords, int offset_x, int offset_y) {
  for (auto coord: coords) {
    Cell cell = Cell(coord[0] + offset_x, coord[1] + offset_y, type);
    cell.attach(td);
    if (gd)
      cell.attach(gd);
    cells.push_back(cell);
  }
}

vector<Cell> Block::positions() {
  return cells;
}

void Block::down() {
  shift(0, 1);
  y++;
}

void Block::left() {
  shift(-1, 0);
  x--;
}

void Block::right() {
  shift(1, 0);
  x++;
}

void Block::clockwise() {
  vector<int> vals = maxMin();
  for (auto &cell: cells) {
    Info info = cell.getInfo();
    cell.setCoords(info.x - (info.x - vals[3]) + (vals[2] - info.y),
                   info.y - (vals[1] - info.x) + (vals[2] - info.y));
  }
}

void Block::cclockwise() {
  vector<int> vals = maxMin();
  for (auto &cell: cells) {
    Info info = cell.getInfo();
    cell.setCoords(info.x - (info.x - vals[3]) + (info.y - vals[0]),
                   info.y - (info.x - vals[3]) + (vals[2] - info.y));
  }
}

int Block::getX() const {
  return x;
}

int Block::getY() const {
  return y;
}

int Block::colsOccupied(int r) {
  int total = 0;
  for (auto &cell : cells) {
    if (cell.getInfo().y == r) {
      total++;
    }
  }
  return total;
}

void Block::remove(int r) {
  for (int i = 0; i < cells.size(); i++) {
    if(cells[i].getInfo().y == r) {
      cells[i].notifyObservers(true);
      cells.erase(cells.begin()+i);
      i--;
    }
  }
}

void Block::dropAbove(int r) {
  for (auto &cell : cells) {
    Info info = cell.getInfo();
    if (info.y < r) {
      cell.notifyObservers(true);
      cell.setCoords(info.x, info.y + 1);
    }
  }
  draw();
} 

void Block::clear() {
  for (auto &cell: cells)
    cell.notifyObservers(true);
}

void Block::shift(int rightBy, int downBy) {
  for (auto &cell: cells) {
    Info info = cell.getInfo();
    cell.setCoords(info.x + rightBy, info.y + downBy);
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

bool Block::isHeavy() const {
  return level >= 3;
}

int Block::getLevel() const {
  return level;
}

bool Block::isEmpty() const {
  return cells.empty();
}
