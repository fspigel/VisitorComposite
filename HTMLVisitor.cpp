#include "HTMLVisitor.h"
#include "Component.h"
#include "Composite.h"
#include <iostream>

void HTMLVisitor::Transform(Component * c){
    for(auto & comp : c->mChildren) comp->accept(this);
}

void HTMLVisitor::Transform(Title * t){
    std::cout << "Applying transform to TITLE!" << std::endl;
    t->text = "<h1>" + t->text + "</h1>";
    for(auto & comp : t->mChildren) comp->accept(this);
}

void HTMLVisitor::Transform(Chapter * c){
    std::cout << "Applying transform to CHAPTER!" << std::endl;
    c->text = "<h2>" + c->text + "</h2>";
    for(auto & comp : c->mChildren) comp->accept(this);
}

void HTMLVisitor::Transform(Paragraph * p){
    std::cout << "Applying transform to PARAGRAPH!" << std::endl;
    for(auto & comp : p->mChildren) comp->accept(this);
}
