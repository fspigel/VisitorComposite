#ifndef ITERATOR_H_INCLUDED
#define ITERATOR_H_INCLUDED
#include <stack>
#include "Component.h"

class Iterator {
public:
    Iterator(Component *);

    bool isDone();

    void iterate();

    Component * first(){return _first;}
    Component * current(){return _current;}


private:
    Component * _first;
    Component * _current;
    Component * _last;

    std::stack<Component*> compStack;
};

#endif // ITERATOR_H_INCLUDED
