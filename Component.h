#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED
#include <vector>
#include <fstream>

class HTMLVisitor;

class Component {
public:
    enum CompType {title, chapter, paragraph};

    Component() : mChildren(), mParent(nullptr) {}

    void addComponent(Component *);

    Component * removeComponent(const Component *);

    void read(std::ifstream &);
    void LoadNextBlock(std::ifstream &, std::string &);
    bool HasChapter();
    CompType type(std::string);

    std::vector<Component *> mChildren;
    Component * mParent;

    std::string text;

    CompType compType;

    //Visitor:
    virtual void accept(HTMLVisitor *);
};

#endif
