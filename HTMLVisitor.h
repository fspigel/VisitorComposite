#ifndef HTMLVISITOR_H_INCLUDED
#define HTMLVISITOR_H_INCLUDED

class Component;
class Title;
class Chapter;
class Paragraph;

class HTMLVisitor {
public:
    void Transform(Component *);
    void Transform(Title *);
    void Transform(Chapter *);
    void Transform(Paragraph *);
};
#endif
