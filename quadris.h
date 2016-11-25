#ifndef _QUADRIS_H_
#define _QUADRIS_H_
#include <memory>
#include "quadris_model.h"

class Quadris {
public:
  Quadris(int, char **);
  void start();

private:
  std::unique_ptr<QuadrisModel> model;
  bool text;
  unsigned seed;
  std::string script_file;
  int start_level;
  bool cmdMatch(std::string, int, std::string);
  void init();
};

#endif
