#include "quadris_model.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
using namespace std;

int QuadrisModel::high_score = 0;

QuadrisModel::QuadrisModel(): td{TextDisplay()}, 
current_block{Block(BlockType::Empty, &td)}, next_block{Block(BlockType::Empty, &td)} {
  score = 0;
  seed = 0;
  level = 0;
  sequence_file = "sequence.txt";
  file_in = ifstream(sequence_file);
  // load two random blocks: one for current and one for next block
  nextBlock();
  nextBlock();
}

void QuadrisModel::down(int m) {
  for (int i = 0; i < m; ++i){
    if(canDown()) {
      current_block.down();
    }
  }
}

void QuadrisModel::right(int m) {
  for (int i = 0; i < m; ++i){
    if (canRight()) {
      current_block.right();
    }
  }
  // takes care of heaviness - all we need
  if (level >= 3)
    down(1);
}

void QuadrisModel::left(int m) {
  for (int i = 0; i < m; ++i)
    if (canLeft()) {
      current_block.left();
    }
  if (level >= 3)
    down(1);
}

void QuadrisModel::drop(int m) {
  for (int i = 0; i < m; ++i) {
    while(canDown()) {
      current_block.down();
    }
    blocks.push_back(current_block);
    nextBlock();
  }
}

void QuadrisModel::clockwise(int m) {
  for (int i = 0; i < m; ++i)
    current_block.clockwise();
  if (level >= 3)
    down(1);
}

void QuadrisModel::cclockwise(int m) {
  for (int i = 0; i < m; ++i)
    current_block.cclockwise();
  if (level >= 3)
    down(1);
}

void QuadrisModel::levelUp(int m) {
  for (int i = 0; i < m; ++i) {
    if (level != 4)
      ++level;
  }
}

void QuadrisModel::levelDown(int m) {
  for (int i = 0; i < m; ++i) {
    if (level != 0)
      --level;
  }
}

bool QuadrisModel::isOver() {
  return false;
}

void QuadrisModel::clearRow() {

}

bool QuadrisModel::canDown() {
  return canMove(0, 1);
}

bool QuadrisModel::canLeft() {
  return canMove(-1, 0);
}

bool QuadrisModel::canRight() {
  return canMove(1, 0);
}

bool QuadrisModel::canMove(int x, int y) {
  vector<Info> current_positions;
  for (auto cell : current_block.positions()) {
    Info info = cell.getInfo();
    info.x += x;
    info.y += y;
    // check that the new position is within the grid
    if (info.x < 0 || info.x >= 11 || info.y < -3 || info.y >= 15) {
      return false;
    }
    current_positions.push_back(info);
  }
  //check that the current spot is not taken up by the currently occupied positions
  for(auto position : positions) {
    for(auto updated_position : current_positions) {
      //cout << "(" << updated_position.x << ", " << updated_position.y << ")" << endl;
      //cout << "(" << position.x << "," << position.y << ")" << endl;
      //cout << (updated_position.x == position.x && updated_position.y == position.x) << endl;
      if (updated_position.x == position.x && updated_position.y == position.y) {
        return false;
      } 
    }
  }
  return true;
}

void QuadrisModel::nextBlock() {
  updatePositions();
  // distrubtion where all reals between 0 and 1 have equal probability
  uniform_real_distribution<double> distribution(0.0, 1.0);
  // create a seed based on current time so that we don't always have the same blocks
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  double random = distribution(generator);

  // make the next block the current block
  current_block = next_block;
  current_block.draw();

  if (level == 0) {
    string type;
    file_in >> type;
    if (type == "Z") {
      next_block = Block(BlockType::ZBlock, &td);
    } else if (type == "S") {
      next_block = Block(BlockType::SBlock, &td);
    } else if (type == "L") {
      next_block = Block(BlockType::LBlock, &td);
    } else if (type == "J") {
      next_block = Block(BlockType::JBlock, &td);
    } else if (type == "I") {
      next_block = Block(BlockType::IBlock, &td);
    } else if (type == "O") {
      next_block = Block(BlockType::OBlock, &td);
    } else if (type == "T") {
      next_block = Block(BlockType::TBlock, &td);
    } 
  } else if (level == 1) {
    if (random <= 1.0/12.0) {
      next_block = Block(BlockType::ZBlock, &td);
    } else if (random <= 1.0/6.0) {
      next_block = Block(BlockType::SBlock, &td);
    } else if (random <= 2.0/6.0) {
      next_block = Block(BlockType::LBlock, &td);
    } else if (random <= 3.0/6.0) {
      next_block = Block(BlockType::JBlock, &td);
    } else if (random <= 4.0/6.0) {
      next_block = Block(BlockType::IBlock, &td);
    } else if (random <= 5.0/6.0) {
      next_block = Block(BlockType::OBlock, &td);
    } else {
      next_block = Block(BlockType::TBlock, &td);
    }
  } else if (level == 2) {
    if (random <= 1.0/7.0) {
      next_block = Block(BlockType::ZBlock, &td);
    } else if (random <= 2.0/7.0) {
      next_block = Block(BlockType::SBlock, &td);
    } else if (random <= 3.0/7.0) {
      next_block = Block(BlockType::LBlock, &td);
    } else if (random <= 4.0/7.0) {
      next_block = Block(BlockType::JBlock, &td);
    } else if (random <= 5.0/7.0) {
      next_block = Block(BlockType::IBlock, &td);
    } else if (random <= 6.0/7.0) {
      next_block = Block(BlockType::OBlock, &td);
    } else {
      next_block = Block(BlockType::TBlock, &td);
    }
  } else {
    if (random <= 2.0/9.0) {
      next_block = Block(BlockType::ZBlock, &td);
    } else if (random <= 4.0/9.0) {
      next_block = Block(BlockType::SBlock, &td);
    } else if (random <= 5.0/9.0) {
      next_block = Block(BlockType::LBlock, &td);
    } else if (random <= 6.0/9.0) {
      next_block = Block(BlockType::JBlock, &td);
    } else if (random <= 7.0/9.0) {
      next_block = Block(BlockType::IBlock, &td);
    } else if (random <= 8.0/9.0) {
      next_block = Block(BlockType::OBlock, &td);
    } else {
      next_block = Block(BlockType::TBlock, &td);
    }
  }
}

void QuadrisModel::updatePositions() {
  positions.clear();
  for(auto block : blocks) {
    for(auto position : block.positions()) {
      positions.push_back(position.getInfo());
    }
  }
}

std::ostream &operator<<(std::ostream &out, const QuadrisModel &model) {
  cout << "\nLevel:" << setw(9) << model.level << endl;
  cout << "Score:" << setw(9) << model.score << endl;
  cout << "Hi Score:" << setw(6) << model.high_score << endl;
  cout << "-----------" << endl;
  cout << model.td;
  cout << "-----------" << endl;
  cout << "Next:" << endl;

  if (model.next_block.type == BlockType::ZBlock)
    cout << "ZZ\n ZZ" << endl;
  else if (model.next_block.type == BlockType::SBlock)
    cout << " SS\nSS" << endl;
  else if (model.next_block.type == BlockType::LBlock)
    cout << "  L\nLLL" << endl;
  else if (model.next_block.type == BlockType::JBlock)
    cout << "J  \nJJJ" << endl;
  else if (model.next_block.type == BlockType::IBlock)
    cout << "IIII" << endl;
  else if (model.next_block.type == BlockType::OBlock)
    cout << "OO\nOO" << endl;
  else if (model.next_block.type == BlockType::TBlock)
    cout << "TTT\n T" << endl;

  return out;
}
