#include <string>
#include <iostream>
#include <sstream>
#include "quadris.h"
using namespace std;

Quadris::Quadris(int argc, char *argv[]): argc{argc}, argv{argv}, 
  level{0}, model{QuadrisModel()} {}

// allows for shorter commands: eg "lef" will work for "left"
bool cmdMatch(string in, int min, string cmd) {
  if (in.length() < min || in.length() > cmd.length())
    return false;
  for (int i = 0; i < in.length(); ++i) {
    if (in[i] != cmd[i])
      return false;
  }
  return true;
}

void Quadris::start() {
  string cmd, sequence_file;
  int mult;
  cout << model;

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
      cin >> sequence_file;
      //model.setSequence(sequence_file);
    }
    else if (cmdMatch(cmd, 1, "norandom")) {}
    else if (cmdMatch(cmd, 2, "random")) {}
    else if (cmdMatch(cmd, 2, "restart")) {}
    else if (cmdMatch(cmd, 1, "hint")) {}
    else {
      for (int i = 0; i < mult; ++i) {
        if (cmdMatch(cmd, 6, "levelup")) {
          if (level < 4) {
            ++level;
            //model.levelup();
          }
        }
        else if (cmdMatch(cmd, 6, "leveldown")) {
          if (level > 0) {
            ++level;
            //model.leveldown();
          }
        }
        else if (cmdMatch(cmd, 3, "left"))
          model.left();
        else if (cmdMatch(cmd, 2, "right"))
          model.right();
        else if (cmdMatch(cmd, 2, "down"))
          model.down();
        else if (cmdMatch(cmd, 2, "drop"))
          model.drop();
        else if (cmdMatch(cmd, 2, "clockwise"))
          model.clockwise();
        else if (cmdMatch(cmd, 2,"cclockwise"))
          model.cclockwise();
        else
          cout << "Invalid or ambiguous command" << endl;
      }
    }
    cout << model;
  }
}
