#ifndef _OBSERVER_H_
#define _OBSERVER_H_
class Info;

class Observer {
 public:
  virtual void notify(Info info) = 0; 
  virtual ~Observer() = default;
};
#endif
