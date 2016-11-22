#ifndef _QUADRIS_H_
#define _QUADRIS_H_
#include "quadris_model.h"

class Quadris {
public:
  Quadris(int, char **);
  void start();

private:
  QuadrisModel model;
  int argc;
  char **argv;
  bool cmdMatch(std::string, int, std::string);
};

#endif
