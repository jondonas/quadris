#include "block.h"
#include "info.h"
#include "block_type.h"
#include <iostream>
#include <vector>
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
}

void Block::cclockwise() {
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
