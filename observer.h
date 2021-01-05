#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;

class Observer {
  public:

    virtual void notify( Subject & whoNotified ) = 0;
    virtual ~Observer() = default;
    virtual std::string getName() = 0;
    
};

#endif
