#ifndef RCObject_h
#define RCObject_h

class RCObject {
  
protected:
  RCObject(): refCount(0), shareable(true){}
  RCObject(const RCObject&):refCount(0),shareable(true){}
  RCObject& operator=(const RCObject&) {return *this;}
  virtual ~RCObject()=0;
  
public:
  void addReference(){++refCount;}
  void removeReference(){if(--refCount==0) delete this;}
  void markUnshareable(){shareable=false;}
  bool isShareable() const {return shareable;}
  bool isShared() const {return refCount>1;}
  int getRefCount() const {return refCount;}
  
  
private:
  int refCount;
  bool shareable;
};

#endif