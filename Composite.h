#ifndef COMPOSITE_H_INCLUDED
#define COMPOSITE_H_INCLUDED
#include "Component.h"
#include "HTMLVisitor.h"
#include <string>

class Title : public Component {
    public:
        Title(std::string str){
            text = str;
            compType = title;
        }
        void accept(HTMLVisitor * v){v->Transform(this);}
};

class Chapter : public Component {
    public:
        Chapter(std::string str){
            text = str;
            compType = chapter;
        }
        void accept(HTMLVisitor * v){v->Transform(this);}
};

class Paragraph : public Component {
    public:
        Paragraph(std::string str){
            text = str;
            compType = paragraph;
        }
        void accept(HTMLVisitor * v){v->Transform(this);}
};

#endif
