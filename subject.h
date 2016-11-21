#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "info.h"
class Observer;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);  
  void notifyObservers(bool);
  virtual Info getInfo() const = 0;
};

#endif
