#ifndef RCPtr_imp_h
#define RCPtr_imp_h

template<class T>
void RCPtr<T>::init()
{
  if(pointee==0) return;
  if(pointee->isShareable() == false) {
    pointee= new T(*pointee);
  }
  pointee->addReference();
}


template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr<T>& rhs)
{
  if (pointee != rhs.pointee) {
    T* oldPointee = pointee;
    pointee = rhs.pointee;
    init();
    if(oldPointee)
      oldPointee->removeReference();
  }
  return *this;
}


#endif
