#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED

#include "NonCopyable.h"
#include "NonMovable.h"

// Singleton class: only allow one copy of class
class Singleton : public NonMovable, public NonCopyable {

};

#endif // SINGLETON_H_INCLUDED