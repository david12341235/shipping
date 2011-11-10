// Copyright (C) 1993-2002 David R. Cheriton.  All rights reserved.

#ifndef FWK_PTR_H
#define FWK_PTR_H

#ifdef _MSC_VER // Visual Studio pointlessly warns about multiple assignment operators, even though they both work fine
  #pragma warning(disable: 4522)
  #pragma warning (disable:4250)
#endif

namespace Fwk {

template <class T>
class Ptr {
  public:
    Ptr( T *ptr = 0 );
    Ptr( const Ptr<T>& mp );
    ~Ptr();
    void operator=( const Ptr<T>& mp );
    void operator=( Ptr<T>& mp );
    bool operator==( const Ptr<T>& mp ) const { return mp.value_ == value_; }
    bool operator!=( const Ptr<T>& mp ) const { return mp.value_ != value_; }
    const T * operator->() const { return value_; }
    T * operator->() { return (T *) value_; }
    T * ptr() const { return (T *) value_; }
//    operator bool() const { return value_ ? 1 : 0; }

    template <class OtherType>
    operator Ptr<OtherType>() const {
        return Ptr<OtherType>( value_ ); }

protected:
    T *value_;
};

template<class T>
Ptr<T>::Ptr( T * ptr  ) : value_(ptr) {
    if( value_ ) value_->newRef();
  }

template<class T>
Ptr<T>::Ptr( const Ptr<T>& mp ) : value_(mp.value_) {
    if( value_ ) value_->newRef();
  }

template<class T>
Ptr<T>::~Ptr() {
    if( value_) value_->deleteRef();
  }

template<class T> void
Ptr<T>::operator=( const Ptr<T>& mp ) {
    const T * save = value_;
    value_ = mp.value_;
    if( value_ ) value_->newRef();
    if( save ) save->deleteRef();
  }

template<class T> void
Ptr<T>::operator=( Ptr<T>& mp ) {
    T * save = value_;
    value_ = mp.value_;
    if( value_ ) value_->newRef();
    if( save ) save->deleteRef();
  }

}
#endif /* PTR_h */
