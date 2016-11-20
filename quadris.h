#ifndef _QUADRIS_H_
#define _QUADRIS_H_
#include "quadris_model.h"

class Quadris {
public:
  Quadris(std::string);
  void commmand (std::string);

private:
  QuadrisModel &model;
}

#endif
