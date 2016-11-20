#include <string>
#include <iostream>
#include <sstream>
#include "quadris.h"
using namespace std;

Quadris::Quadris(int argc, char *argv[]): argc{argc}, argv{argv}, 
  level{0}, model{QuadrisModel()} {}

void Quadris::start() {
  string cmd, sequence_file;
  int mult;

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

    if (cmd == "sequence") {
      cin >> sequence_file;
      //model.setSequence(sequence_file);
    }
    else if (cmd == "norandom") {}
    else if (cmd == "random") {}
    else if (cmd == "restart") {}
    else if (cmd == "hint") {}
    else {
      for int (i = 0; i < mult; ++i) {
        if (cmd == "levelup") {
          if (level < 4) {
            ++level;
            //model.levelup();
          }
        }
        else if (cmd == "leveldown") {
          if (level > 0) {
            ++level;
            //model.leveldown();
          }
        }
        else if (cmd == "left")
          model.left();
        else if (cmd == "right")
          model.right();
        else if (cmd == "down")
          model.down();
        else if (cmd == "drop")
          model.drop();
        else if (cmd == "clockwise")
          model.clockwise();
        else if (cmd == "cclockwise")
          model.cclockwise();
      }
    }
  }
}
