#include "subject.h"
#include "observer.h"
#include "block_type.h"

void Subject::attach(Observer *o) { 
  observers.push_back(o);    
}

void Subject::notifyObservers(bool clear) {
  for (auto it = observers.begin(); it != observers.end(); ++it) {
    if (clear) {
      Info info = getInfo();
      (*it)->notify({info.x, info.y, BlockType::Empty});
    }
    else
      (*it)->notify(getInfo());
  }
}

