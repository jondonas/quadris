#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <vector>
#include "observer.h"
#include "window.h"
#include "info.h"

class GraphicsDisplay: public Observer {
  Xwindow xw;
  bool hold;
  void drawCell(int, int, int);

 public:
  GraphicsDisplay(bool);
  void notify(Info info) override;
  void drawLegend(int, int, int, std::vector<std::vector<int>>, int, std::vector<std::vector<int>>, int);
  ~GraphicsDisplay();

};

#endif
