#include <string>
#include <iostream>
#include <sstream>
#include "quadris.h"
using namespace std;

Quadris::Quadris(int argc, char *argv[]): text{false}, seed{0}, script_file{"sequence.txt"}, start_level{0} {
  for (int i = 0; i < argc; ++i) {
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
  }
  init();
}

void Quadris::start() {
  string cmd;
  int mult;
  cout << *model;

  while (cin >> cmd) {
    mult = 1;

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
    // todo: hint
    else if (cmdMatch(cmd, 1, "hint")) {}
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
    else if (cmdMatch(cmd, 2, "cclockwise"))
      model->cclockwise(mult);
    else
      cout << "Invalid or ambiguous command" << endl;
    
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
