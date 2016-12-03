#include <string>
#include <iostream>
#include <sstream>
#include "quadris.h"
using namespace std;

Quadris::Quadris(int argc, char *argv[]): text{false}, seed{0}, script_file{"sequence.txt"}, start_level{0} {
  for (int i = 1; i < argc; ++i) {
    string arg(argv[i]);
    if (arg == "-text") {
      text = true;
    }
    else if (arg == "-seed") {
      ++i;
      stringstream(argv[i]) >> seed;
    }
    else if (arg == "-scriptfile") {
      ++i;
      script_file = string(argv[i]);
    }
    else if (arg == "-startlevel") {
      ++i;
      stringstream(argv[i]) >> start_level;
    }
    else if (arg == "-h" || arg == "--help")
      usage();
    else {
      cout << "**INVALID OPTION**" << endl;
      usage();
    }
  }
  init();
}

void Quadris::start() {
  string cmd;
  int mult;
  bool last_hint = false;
  cout << *model;

  while (cin >> cmd) {
    mult = 1;
    if (last_hint) {
      last_hint = false;
      model->clearHint();
    }

    if (47 < cmd[0] && cmd[0] < 58) {
      string num = "";
      int i = 0;
      while (47 < cmd[i] && cmd[i] < 58) {
        num += cmd[i];
        ++i;
      }
      stringstream(num) >> mult;
      cmd = cmd.substr(i, cmd.size());
    }

    if (cmdMatch(cmd, 1, "sequence")) {
      cin >> script_file;
      model->setSeqFile(script_file);
    }
    else if (cmdMatch(cmd, 1, "norandom"))
      model->setRandom(false);
    else if (cmdMatch(cmd, 2, "random"))
      model->setRandom(true);
    else if (cmdMatch(cmd, 2, "restart"))
      init();
    else if (cmdMatch(cmd, 2, "hint")) {
      last_hint = true;
      model->getHint();
    } else if (cmdMatch(cmd, 2, "hold"))
      model->hold();
    else if (cmdMatch(cmd, 6, "levelup"))
      model->levelUp(mult);
    else if (cmdMatch(cmd, 6, "leveldown"))
      model->levelDown(mult);
    else if (cmdMatch(cmd, 3, "left"))
      model->left(mult);
    else if (cmdMatch(cmd, 2, "right"))
      model->right(mult);
    else if (cmdMatch(cmd, 2, "down"))
      model->down(mult);
    else if (cmdMatch(cmd, 2, "drop"))
      model->drop(mult);
    else if (cmdMatch(cmd, 2, "clockwise"))
      model->clockwise(mult);
    else if (cmdMatch(cmd, 2, "counterclockwise"))
      model->cclockwise(mult);
    else if (cmdMatch(cmd, 1, "auto"))
      model->automate(mult);
    else if (cmd == "I")
      model->swapType(BlockType::IBlock);
    else if (cmd == "J")
      model->swapType(BlockType::JBlock);
    else if (cmd == "L")
      model->swapType(BlockType::LBlock);
    else if (cmd == "O")
      model->swapType(BlockType::OBlock);
    else if (cmd == "S")
      model->swapType(BlockType::SBlock);
    else if (cmd == "Z")
      model->swapType(BlockType::ZBlock);
    else if (cmd == "T")
      model->swapType(BlockType::TBlock);
    else
      cout << "Invalid or ambiguous command" << endl;

    if (model->isOver()) {
      cout << "Game Over! You scored " << model->getScore() << " points." << endl;
      init();
    }
    
    cout << *model;
  }
}

bool Quadris::cmdMatch(string in, int min, string cmd) {
  if (in.length() < min || in.length() > cmd.length())
    return false;
  for (int i = 0; i < in.length(); ++i) {
    if (in[i] != cmd[i])
      return false;
  }
  return true;
}

void Quadris::init() {
  model = make_unique<QuadrisModel>(text, seed, script_file, start_level);
}

void Quadris::usage() {
  cout << endl <<
  "QUADRIS. Made by Ryan Quanz and Jonathan Donas.\n"
  "Usage: ./quadris [options]\n\n"
  
  "Options:\n"
  "  -text                    Run in text-only mode\n"
  "  -seed [seed]             Set the random number generator's seed\n" 
  "  -scriptfile [file]       Use [file] instead of the default sequence.txt\n"
  "  -startlevel [n]          Start game in level [n]\n"
  "  -h  or  --help           Display this help message\n\n"
  
  "In-game commands:\n"
  "  left\n"
  "  right\n"
  "  down\n"
  "  clockwise\n"
  "  counterclockwise\n"
  "  drop\n"
  "  levelup\n"
  "  leveldown\n"
  "  restart\n"
  "  norandom                 Make levels 3 and 4 read from input file\n"
  "  random                   Make levels 3 and 4 random (default)\n"
  "  sequence [file]          Change sequence file\n"
  "  I, J, L, etc.            Replace current block with specified block\n"
  "  hint                     Display a hint\n"
  "  auto                     Makes the best move for you\n\n"
  
  "Commands can be shortened (eg. counterclockwise -> co)\n"
  "and executed multiple times (eg. 2left)\n"
  << endl;

  exit(1);
}
