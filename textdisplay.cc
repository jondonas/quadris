#include <utility>
#include <vector>
#include "textdisplay.h"
#include "info.h"
using namespace std;

// empty space is a '-' for now, to help with debugging
TextDisplay::TextDisplay() {
  for (int i = 0; i < 15; ++i) {
    vector<char> inner;
    for (int ii = 0; ii < 11; ++ii)
      inner.push_back('-');
    theDisplay.push_back(inner);
  }
}

void TextDisplay::notify(Info info) {
  if(info.x < 0 || info.x > 10 || info.y < 0 || info.y > 14)
    return;
  if (info.type == BlockType::Empty)
    theDisplay[info.y][info.x] = '-';
  else if (info.type == BlockType::IBlock)
    theDisplay[info.y][info.x] = 'I';
  else if (info.type == BlockType::JBlock)
    theDisplay[info.y][info.x] = 'J';
  else if (info.type == BlockType::LBlock)
    theDisplay[info.y][info.x] = 'L';
  else if (info.type == BlockType::OBlock)
    theDisplay[info.y][info.x] = 'O';
  else if (info.type == BlockType::SBlock)
    theDisplay[info.y][info.x] = 'S';
  else if (info.type == BlockType::ZBlock)
    theDisplay[info.y][info.x] = 'Z';
  else if (info.type == BlockType::TBlock)
    theDisplay[info.y][info.x] = 'T';
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
  for (int i = 0; i < 15; ++i) {
    for (int ii = 0; ii < 11; ++ii)
      out << td.theDisplay[i][ii];
    out << endl;
  }
  return out;
}
