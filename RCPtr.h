#ifndef RCPtr_h
#define RCPtr_h

template<class T>
class RCPtr
{
  T* pointee;
  void init();
  
public:
  RCPtr(T* realPtr=0): pointee(realPtr) { init();}
  RCPtr(const RCPtr& rhs): pointee(rhs.pointee)
  { init();}
  ~RCPtr(){ if (pointee) pointee->removeReference();}
  RCPtr& operator=(const RCPtr& rhs);
  T* operator->() const{return pointee;}
  T& operator*() const{return *pointee;}
};



#include "RCPtr_imp.h"
#endif