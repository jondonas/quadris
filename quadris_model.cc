#include "quadris_model.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

QuadrisModel::QuadrisModel(): td{TextDisplay()}, 
current_block{Block(BlockType::Empty, &td)} {
  score = 0;
  seed = 0;
  level = 0;
  //high_score = 0;
  sequence_file = "sequence.txt";
  file_in = ifstream(sequence_file);
  nextBlock();
}

void QuadrisModel::down() {
  current_block.down();
}

void QuadrisModel::right() {
  current_block.right();
}

void QuadrisModel::left() {
  current_block.left();
}

void QuadrisModel::drop() {

}

void QuadrisModel::clockwise() {
  current_block.clockwise();
}

void QuadrisModel::cclockwise() {
  current_block.cclockwise();
}

void QuadrisModel::levelUp() {
  if (level != 4) {
    ++level;
  }
}

void QuadrisModel::levelDown() {
  if (level != 0) {
    --level;
  }
}

bool QuadrisModel::isOver() {
  false;
}

void QuadrisModel::clearRow() {

}

void QuadrisModel::nextBlock() {
  // distrubtion where all reals between 0 and 1 have equal probability
  uniform_real_distribution<double> distribution(0.0, 1.0);
  // create a seed based on current time so that we don't always have the same blocks
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  double random = distribution(generator);
  if (level == 0) {
    string type;
    file_in >> type;
    if (type == "Z") {
      current_block = Block(BlockType::ZBlock, &td);
    } else if (type == "S") {
      current_block = Block(BlockType::SBlock, &td);
    } else if (type == "L") {
      current_block = Block(BlockType::LBlock, &td);
    } else if (type == "J") {
      current_block = Block(BlockType::JBlock, &td);
    } else if (type == "I") {
      current_block = Block(BlockType::IBlock, &td);
    } else if (type == "O") {
      current_block = Block(BlockType::OBlock, &td);
    } else if (type == "T") {
      current_block = Block(BlockType::TBlock, &td);
    } 
  } else if (level == 1) {
    if (random <= 1.0/12.0) {
      current_block = Block(BlockType::ZBlock, &td);
    } else if (random <= 1.0/6.0) {
      current_block = Block(BlockType::SBlock, &td);
    } else if (random <= 2.0/6.0) {
      current_block = Block(BlockType::LBlock, &td);
    } else if (random <= 3.0/6.0) {
      current_block = Block(BlockType::JBlock, &td);
    } else if (random <= 4.0/6.0) {
      current_block = Block(BlockType::IBlock, &td);
    } else if (random <= 5.0/6.0) {
      current_block = Block(BlockType::OBlock, &td);
    } else {
      current_block = Block(BlockType::TBlock, &td);
    }
  } else if (level == 2) {
    if (random <= 1.0/7.0) {
      current_block = Block(BlockType::ZBlock, &td);
    } else if (random <= 2.0/7.0) {
      current_block = Block(BlockType::SBlock, &td);
    } else if (random <= 3.0/7.0) {
      current_block = Block(BlockType::LBlock, &td);
    } else if (random <= 4.0/7.0) {
      current_block = Block(BlockType::JBlock, &td);
    } else if (random <= 5.0/7.0) {
      current_block = Block(BlockType::IBlock, &td);
    } else if (random <= 6.0/7.0) {
      current_block = Block(BlockType::OBlock, &td);
    } else {
      current_block = Block(BlockType::TBlock, &td);
    }
  } else {
    if (random <= 2.0/9.0) {
      current_block = Block(BlockType::ZBlock, &td, true);
    } else if (random <= 4.0/9.0) {
      current_block = Block(BlockType::SBlock, &td, true);
    } else if (random <= 5.0/9.0) {
      current_block = Block(BlockType::LBlock, &td, true);
    } else if (random <= 6.0/9.0) {
      current_block = Block(BlockType::JBlock, &td, true);
    } else if (random <= 7.0/9.0) {
      current_block = Block(BlockType::IBlock, &td, true);
    } else if (random <= 8.0/9.0) {
      current_block = Block(BlockType::OBlock, &td, true);
    } else {
      current_block = Block(BlockType::TBlock, &td, true);
    }
  }
}

std::ostream &operator<<(std::ostream &out, const QuadrisModel &model) {
  std::cout << model.td;
  return out;
}
