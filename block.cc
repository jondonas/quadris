#include "block.h"
#include "info.h"
#include "block_type.h"
#include <iostream>
#include <vector>
using namespace std;

void init(vector<Cell> &cells, BlockType type, TextDisplay *td,
vector<vector<int>> coords) {
  for (auto coord: coords)
    cells.push_back(Cell(coord[0], coord[1], type, td));
}

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

vector<Cell> &Block::positions() {
  return cells;
}

// this helper ensures that the textdisplay is rendered properly. I can explain 
// if you wonder why we need it
void shift(Cell &cell, TextDisplay *td, vector<vector<int>> alreadyUpdated, int x, int y) {
  bool alreadySet = false;
  Info info = cell.getInfo();

  for (int i = 0; i < alreadyUpdated.size(); ++i) {
    if (alreadyUpdated[i][0] == info.x && alreadyUpdated[i][1] == info.y)
      alreadySet = true;
  }

  if (!alreadySet)
    td->notify({info.x, info.y, BlockType::Empty});

  cell.setCoords(x, y);
}

// this helper moves the cells. Will need to add bounds checking to this
void move(vector<Cell> &cells, TextDisplay *td, int downBy, int rightBy) {
  vector<vector<int>> alreadyUpdated;
  for (int i = 0; i < cells.size(); ++i) {
    Info info = cells[i].getInfo();
    shift(cells[i], td, alreadyUpdated, info.x + rightBy, info.y + downBy);
    alreadyUpdated.push_back({info.x + rightBy, info.y + downBy});
  }
}

void Block::down() {
  move(cells, td, 1, 0);
}

void Block::left() {
  move(cells, td, 0, -1);
}

void Block::right() {
  move(cells, td, 0, 1);
}

void Block::clockwise() {
}

void Block::cclockwise() {
}
