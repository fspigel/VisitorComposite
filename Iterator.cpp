#include "Iterator.h"
#include <vector>

void Iterator::iterate(){
    Component * node = compStack.top();
    compStack.pop();
    if(node != nullptr){
        for(std::vector<Component*>::iterator it = node->mChildren.begin(); it != node->mChildren.end(); ++it){
            compStack.push(*it);
        }
    }
    _current = node;
}

Iterator::Iterator(Component * comp){
    compStack.push(comp);
}

bool Iterator::isDone(){return compStack.empty();}
