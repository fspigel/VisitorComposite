#include "Component.h"
#include "Composite.h"
#include "HTMLVisitor.h"
#include <stdexcept>
#include <iostream>

using namespace std;

void Component::addComponent(Component * comp){
    comp->mParent = this;
    mChildren.push_back(comp);
}

Component * Component::removeComponent(const Component * comp){
    for(std::vector<Component *>::iterator it = mChildren.begin(); it != mChildren.end(); ++it){
        if(comp == *it){
            (*it)->mParent = nullptr;
            auto a = *it;
            mChildren.erase(it);
            return a;
        }
    }
    throw std::runtime_error("Attempted to remove component which is not present in mChildren");
}

void Component::read(std::ifstream & str) {
    string currentBlock;

    //Load first title:
//    LoadNextBlock(str, currentBlock);
//    mChildren.push_back(new Title(currentBlock));
//    cout << currentBlock << endl;

    while(!str.eof()){
        currentBlock.clear();
        LoadNextBlock(str, currentBlock);
        if(currentBlock.empty()) break;
        if(type(currentBlock) == title){
            mChildren.push_back(new Title(currentBlock.substr(2, currentBlock.size()-2)));
        }
        else if(type(currentBlock) == chapter){
            if(!HasTitle()) mChildren.push_back(new Chapter(currentBlock.substr(3, currentBlock.size()-3)));
            else mChildren.back()->mChildren.push_back(new Chapter(currentBlock.substr(3, currentBlock.size()-3)));
        }
        else{
            if(HasTitle()){
                if(mChildren.back()->HasChapter()) mChildren.back()->mChildren.back()->mChildren.push_back(new Paragraph(currentBlock));
                else(mChildren.back()->mChildren.push_back(new Paragraph(currentBlock)));
            }
            else{
                if(HasChapter()) mChildren.back()->mChildren.push_back(new Paragraph(currentBlock));
                else mChildren.push_back(new Paragraph(currentBlock));
            }
        }
    }
}

//Loads the next block of text between two empty lines into 'block'
void Component::LoadNextBlock(ifstream & stream, string & block){
    string currentLine;
    while(!stream.eof() && currentLine.empty()){
        getline(stream, currentLine);
    }

    while(!stream.eof() && !currentLine.empty()){
        block.append(currentLine).append("\n");
        getline(stream, currentLine);
    }

    if(block.size()!=0) block.erase(block.size()-1, 1);
}

bool Component::HasChapter(){
    for(vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it){
        if((*it)->compType == chapter) return true;
    }
    return false;
}

bool Component::HasTitle(){
    for(vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it){
        if((*it)->compType == title) return true;
    }
    return false;
}

Component::CompType Component::type(string s){
    if(!s.substr(0, 2).compare("==")) return chapter;
    else if(!s.substr(0, 1).compare("=")) return title;
    else return paragraph;
}

void Component::print(){
    cout << endl << text << endl;
    for(auto & comp : mChildren) comp->print();
}

void Component::accept(HTMLVisitor * v){
    v->Transform(this);
}
