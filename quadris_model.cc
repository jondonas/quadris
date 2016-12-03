#include "quadris_model.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#define LEVEL_1 { 1.0/12.0, 1.0/6.0, 2.0/6.0, 3.0/6.0, 4.0/6.0, 5.0/6.0 }
#define LEVEL_2 { 1.0/7.0, 2.0/7.0, 3.0/7.0, 4.0/7.0, 5.0/7.0, 6.0/7.0 }
#define LEVEL_3 { 2.0/9.0, 4.0/9.0, 5.0/9.0, 6.0/9.0, 7.0/9.0, 8.0/9.0 }
using namespace std;

int QuadrisModel::high_score = 0;

QuadrisModel::QuadrisModel(bool text, int seed, string script_file, int start_level):
td{make_shared<TextDisplay>()}, gd{nullptr}, current_block{Block(BlockType::Empty, td, gd, 0)}, next_block{BlockType::Empty}, hint_block{Block(BlockType::Empty, td, gd, 0)}, block_random{true}, level{0}, seed{seed}, lost{false} {
  if (start_level >= 0 && start_level <= 4)
    level = start_level;
  
  drops_without_clear = 0;
  score = 0;
  // for now, exit if seq file can't be loaded at start. todo: let user play without
  // loading seq file.
  if (!setSeqFile(script_file))
    exit(1);

  if (!text)
    gd = make_shared<GraphicsDisplay>();
  srand(seed);
  held_block = BlockType::Empty;
  // load two random blocks: one for current and one for next block
  nextBlock();
  nextBlock();

  if (gd)
    drawLegend();
}

bool QuadrisModel::setSeqFile(string seqFile) {
  ifstream temp(seqFile);
  if (!temp.is_open()) {
    cout << "Could not open sequence file." << endl;
    return false;
  }
  file_in = move(temp);
  return true;
}

void QuadrisModel::setRandom(bool rndm) {
  if (level == 3 || level == 4)
    block_random = rndm;
}

void QuadrisModel::down(int m) {
  // model should take care of drawing. This is so the graphics display doesn't
  // draw every single movement when multiplicity is used or you drop a block (so slow!)
  current_block.clear();
  for (int i = 0; i < m; ++i) {
    if(canDown()) {
      current_block.down();
    }
  }
  current_block.draw();
}

void QuadrisModel::right(int m) {
  current_block.clear();
  for (int i = 0; i < m; ++i) {
    if (canRight()) {
      current_block.right();
    }
  }
  if (current_block.isHeavy() && canDown())
    current_block.down();
  current_block.draw();
}

void QuadrisModel::left(int m) {
  current_block.clear();
  for (int i = 0; i < m; ++i) {
    if (canLeft()) {
      current_block.left();
    }
  }
  if (current_block.isHeavy() && canDown())
    current_block.down();
  current_block.draw();
}

void QuadrisModel::drop(int m) {
  for (int i = 0; i < m; ++i) {
    current_block.clear();
    while(canDown()) {
      current_block.down();
    }
    current_block.draw();
    blocks.push_back(current_block);
    clearRows();
    clearBlocks();
    nextBlock();
    if (gd)
      drawLegend();
  }
}

void QuadrisModel::clockwise(int m) {
  current_block.clear();
  for (int i = 0; i < m; ++i) {
    if (canClock()) {
      current_block.clockwise();
    }
  }
  if (current_block.isHeavy() && canDown())
    current_block.down();
  current_block.draw();
}

void QuadrisModel::cclockwise(int m) {
  current_block.clear();
  for (int i = 0; i < m; ++i) {
    if (canCclock()) {
      current_block.cclockwise();
    }
  }
  if (current_block.isHeavy() && canDown())
    current_block.down();
  current_block.draw();
}

void QuadrisModel::levelUp(int m) {
  for (int i = 0; i < m; ++i) {
    if (level == 3) {
      drops_without_clear = 0;
    }
    if (level <  4)
      ++level;
  }
  if (gd)
    drawLegend();
}

void QuadrisModel::levelDown(int m) {
  for (int i = 0; i < m; ++i) {
    if (level != 0)
      --level;
  }
  if (gd)
    drawLegend();
}

void QuadrisModel::hold() {
  if (held_block == BlockType::Empty) {
    held_block = current_block.getType();
    current_block.clear();
    nextBlock();
  } else {
    BlockType type = current_block.getType();
    swapType(held_block);
    held_block = type;
  }
  drawLegend();
}

void QuadrisModel::swapType(BlockType t) {
  int x = current_block.getX();
  int y = current_block.getY();
  int level = current_block.getLevel();
  current_block.clear();
  current_block = Block(t, td, gd, level, x, y);
  current_block.draw();
}

bool QuadrisModel::isOver() {
  return lost;
}

int QuadrisModel::getScore() {
  return score;
}

void QuadrisModel::getHint() {
  hint_block = suggestedBlock();
  hint_block.changeType(BlockType::HintBlock);
  hint_block.draw();
}

void QuadrisModel::clearHint() {
  hint_block.clear();
}

void QuadrisModel::automate(int m) {
  for (int i = 0; i < m; ++i) {
    current_block.clear();
    current_block = suggestedBlock();
    drop(1);
    if (isOver())
      break;
  }
}


void QuadrisModel::clearRows() {
  int rows_cleared = 0;
  for(int r = 14; r >= 0; r--) {
    int cols_occupied = 0;
    for(auto &block : blocks) {
      cols_occupied += block.colsOccupied(r);
    }
    if (cols_occupied == 11) {
      for(auto &block : blocks) {
        block.remove(r);
        block.dropAbove(r);
      }
      rows_cleared++;
      //so we recheck the current row
      r++;
    }
  }
  updatePositions();
  if (rows_cleared > 0) {
    drops_without_clear = 0;
    rows_cleared += level;
    updateScore(rows_cleared * rows_cleared);
  } else {
    drops_without_clear++;
  }
}

void QuadrisModel::clearBlocks() {
  for(int i = 0; i < blocks.size(); i++) {
    if (blocks[i].isEmpty()) {
      int levelScore = 1;
      levelScore += blocks[i].getLevel();
      levelScore *= levelScore;
      updateScore(levelScore);
      blocks.erase(blocks.begin() + i);
      i--;
    }
  }
}

void QuadrisModel::updateScore(int update) {
  score += update;
  if (score > high_score) {
    high_score = score;
  }
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

bool QuadrisModel::canClock() {
  vector<int> vals = current_block.maxMin();
  for (auto cell: current_block.positions()) {
    Info info = cell.getInfo();
    int x = info.x - (info.x - vals[3]) + (vals[2] - info.y);
    int y = info.y - (vals[1] - info.x) + (vals[2] - info.y);
    if (!isOpen(x, y)) {
      return false;
    }
  }
  return true;
}

bool QuadrisModel::canCclock() {
  vector<int> vals = current_block.maxMin();
  for (auto cell: current_block.positions()) {
    Info info = cell.getInfo();
    int x = info.x - (info.x - vals[3]) + (info.y - vals[0]);
    int y = info.y - (info.x - vals[3]) + (vals[2] - info.y);
    if (!isOpen(x, y)) {
      return false;
    }
  }
  return true;
}

// checks absolute position and not relative like canMove.
bool QuadrisModel::isOpen(int x, int y) {
  if (x < 0 || x >= 11 || y < -3 || y >= 15) {
      return false;
  }
  for (auto position: positions) {
    if (x == position.x && y == position.y) {
        return false;
    }
  }
  return true;
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
      if (updated_position.x == position.x && updated_position.y == position.y) {
        return false;
      } 
    }
  }
  return true;
}

void QuadrisModel::nextBlock() {
  updatePositions();

  if (drops_without_clear == 5 && level >= 4) {
    current_block = Block(BlockType::SingleBlock, td, gd, level, 5, 0);
    if (canMove(0, 0)) {
      drop(1);
      drops_without_clear = 0;
    } else {
      lost = true;
    }
    return;
  }

  // distrubtion where all reals between 0 and 1 have equal probability
  double random = getRandom();


  // make the next block the current block
  if (next_block == BlockType::IBlock) {
    current_block = Block(next_block, td, gd, level, 0, 0);
  } else {
    current_block = Block(next_block, td, gd, level, 0, 1);
  }
  // if the current space is occupied the game is over
  if(!canMove(0, 0)) {
    lost = true;
    return;
  }
  current_block.draw();
    
  if (level == 0 || !block_random) {
    string type;
    file_in >> type;
    if (type == "Z") {
      next_block = BlockType::ZBlock;
    } else if (type == "S") {
      next_block = BlockType::SBlock;
    } else if (type == "L") {
      next_block = BlockType::LBlock;
    } else if (type == "J") {
      next_block = BlockType::JBlock;
    } else if (type == "I") {
      next_block = BlockType::IBlock;
    } else if (type == "O") {
      next_block = BlockType::OBlock;
    } else if (type == "T") {
      next_block = BlockType::TBlock;
    } 
  } else  {
    vector<double> probabilities;
    if (level == 1) {
      probabilities = LEVEL_1;
    } else if (level == 2) {
      probabilities = LEVEL_2;
    } else {
      probabilities = LEVEL_3;
    }

    if (random <= probabilities[0]) {
      next_block = BlockType::ZBlock;
    } else if (random <= probabilities[1]) {
      next_block = BlockType::SBlock;
    } else if (random <= probabilities[2]) {
      next_block = BlockType::LBlock;
    } else if (random <= probabilities[3]) {
      next_block = BlockType::JBlock;
    } else if (random <= probabilities[4]) {
      next_block = BlockType::IBlock;
    } else if (random <= probabilities[5]) {
      next_block = BlockType::OBlock;
    } else {
      next_block = BlockType::TBlock;
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

double QuadrisModel::getRandom() {
 return (rand() % 1000) / 1000.0;
}

void QuadrisModel::drawLegend() {
  gd->drawLegend(level, score, high_score, blockPosns(next_block), blockColour(next_block), blockPosns(held_block), blockColour(held_block));
}

std::ostream &operator<<(std::ostream &out, const QuadrisModel &model) {
  cout << endl << "Level:" << setw(9) << model.level << endl;
  cout << "Score:" << setw(9) << model.score << endl;
  cout << "Hi Score:" << setw(6) << model.high_score << endl;
  cout << "  -----------" << endl;
  cout << *(model.td);
  cout << "  -----------" << endl;
  cout << "Next:" << endl;
  printBlock(out, model.next_block);
  cout << "Hold:" << endl;
  printBlock(out, model.held_block);
  return out;
}

ostream &printBlock(ostream &out, BlockType t) {
  if (t == BlockType::ZBlock)
    out << "ZZ\n ZZ" << endl;
  else if (t == BlockType::SBlock)
    out << " SS\nSS" << endl;
  else if (t == BlockType::LBlock)
    out << "  L\nLLL" << endl;
  else if (t == BlockType::JBlock)
    out << "J  \nJJJ" << endl;
  else if (t == BlockType::IBlock)
    out << "IIII" << endl;
  else if (t == BlockType::OBlock)
    out << "OO\nOO" << endl;
  else if (t == BlockType::TBlock)
    out << "TTT\n T" << endl;
  return out;
}

int QuadrisModel::blockColour(BlockType t) {
  if (t == BlockType::ZBlock)
    return Xwindow::Red;
  else if (t == BlockType::SBlock)
    return Xwindow::Green;
  else if (t == BlockType::LBlock)
    return Xwindow::Orange;
  else if (t == BlockType::JBlock)
    return Xwindow::Blue;
  else if (t == BlockType::IBlock)
    return Xwindow::Cyan;
  else if (t == BlockType::OBlock)
    return Xwindow::Yellow;
  else if (t == BlockType::TBlock)
    return Xwindow::Purple;
  return 0;
}

vector<vector<int>> QuadrisModel::blockPosns(BlockType t) {
  if (t == BlockType::ZBlock)
    return {{0,0},{1,0},{1,1},{2,1}};
  else if (t == BlockType::SBlock)
    return {{0,1},{1,1},{1,0},{2,0}};
  else if (t == BlockType::LBlock)
    return {{2,0},{0,1},{1,1},{2,1}};
  else if (t == BlockType::JBlock)
    return {{0,0},{0,1},{1,1},{2,1}};
  else if (t == BlockType::IBlock)
    return {{0,0},{1,0},{2,0},{3,0}};
  else if (t == BlockType::OBlock)
    return {{0,0},{0,1},{1,0},{1,1}};
  else if (t == BlockType::TBlock)
    return {{0,0},{1,0},{2,0},{1,1}};
  return {};
}

/////////////// AI LOGIC ///////////////
// In a perfect world this would have its own class.
// The AI is currently limited to choosing the "best move" that you can get to without
// lateral movements. Eg, if the best move is under an overhang, it won't find it.

Block QuadrisModel::suggestedBlock() {
  Block best_position = current_block;
  int best_score = -100000;
  Block hold_current = current_block;

  // find the "playing field" of the block. Eg, find any barriers that it can't cross
  while (canLeft())
    current_block.left();
  int leftBarrier = current_block.maxMin()[3];
  while (canRight())
    current_block.right();
  int rightBarrier = current_block.maxMin()[1];

  Block top_spot = Block(current_block.getType(), td, gd, level, leftBarrier, current_block.getY());

  // create a "snapshot" of the current grid to use to improve calculation efficiency
  vector<vector<int>> grid;
  for (int i = 0; i < 15; ++i) {
    vector<int> temp;
    for (int ii = 0; ii < 11; ++ii)
      temp.push_back(0);
    grid.push_back(temp);
  }
  for (auto position : positions) {
    if (!(position.y < 0))
      grid[position.y][position.x] = 1;
  }

  // iterate through all possible positions and find the best spot
  for (int i = leftBarrier; i <= rightBarrier; ++i, top_spot.right()) {
    for (int ii = 0; ii < 4; ++ii, top_spot.clockwise()) {
      current_block = top_spot;
      if (!canMove(0,0)) continue;
      while (canDown())
        current_block.down();
      
      // add the current block to a copy of the grid
      vector<vector<int>> temp_grid = grid;
      for (auto cell: current_block.positions()) {
        Info info = cell.getInfo();
        if (!(info.y < 0))
          temp_grid[info.y][info.x] = 1;
      }

      // calculate metrics and score
      int th = totHeight(temp_grid);
      int h = holes(temp_grid);
      int b = bumpiness(temp_grid);
      int cr = completeRows(temp_grid);
      // these numbers determine what makes a "good move"
      // I did a lot of testing and this seems to be the best combination
      // It solves about 7000 moves when you set the seed to 8989898 (highest I got to in testing)
      double block_score = (-0.1 * th) + (-5 * h) + (-1 * b) + pow(2 * cr, 2);

      if (block_score >= best_score) {
        best_score = block_score;
        best_position = current_block;
      }
    }
  }

  current_block = hold_current;
  return best_position;
}

// returns sum of the squares of the heights of columns
int QuadrisModel::totHeight(vector<vector<int>> grid) {
  int th = 0;
  for (int i = 0; i < 11; ++i) {
    int col = colHeight(grid, i);
    // penalize moves that are too close to the top
    th += col * col;
  }

  return th;
}

// returns the number of holes on the layout. A hole is any empty space with a block above
int QuadrisModel::holes(vector<vector<int>> grid) {
  int h = 0;
  for(int i = 0; i < 11; ++i) {
    int empty = 0;
    for(int ii = 0; ii < 15; ++ii) {
      if (grid[ii][i] == 0)
        ++empty;
    }
    h += empty - (15 - colHeight(grid, i));
  }
  
  return h;  
}

// returns the bumpiness of the layout. Higher means less flat.
int QuadrisModel::bumpiness(vector<vector<int>> grid) {
  int b = 0;
  for (int i = 0; i < 10; ++i)
    b += abs(colHeight(grid, i) - colHeight(grid, i + 1));

  return b;
}

// returns the number of filled rows
int QuadrisModel::completeRows(vector<vector<int>> grid) {
  int cr = 0;
  for(int i = 0; i < 15; ++i) {
    int cols_occupied = 0;
    for(int ii = 0; ii < 11; ++ii) {
      if (grid[i][ii] == 1)
        ++cols_occupied;
    }
    if (cols_occupied == 11)
      ++cr;
  }

  return cr;
}

// returns height of a column
int QuadrisModel::colHeight(vector<vector<int>> grid, int col) {
  for (int i = 0; i < 15; ++i) {
    if (grid[i][col] == 1)
      return 15 - i;
  }
  return 0;
}
