#include "HTMLVisitor.h"
#include "Component.h"
#include "Composite.h"
#include <iostream>

void HTMLVisitor::Transform(Component * c){
    c->accept(this);
}

void HTMLVisitor::Transform(Title * t){
    std::cout << "Applying transform to TITLE!" << std::endl;
    t->text = "<h1>" + t->text + "</h1>";
}

void HTMLVisitor::Transform(Chapter * c){
    std::cout << "Applying transform to CHAPTER!" << std::endl;
    c->text = "<h2>" + c->text + "</h2>";
}

void HTMLVisitor::Transform(Paragraph * p){
    std::cout << "Applying transform to PARAGRAPH!" << std::endl;

}
