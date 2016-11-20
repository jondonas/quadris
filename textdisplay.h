#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "info.h"

class TextDisplay: public Observer {
  std::vector<std::vector<char>> theDisplay;
 public:
  TextDisplay();
  void notify(Info) override;
  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
