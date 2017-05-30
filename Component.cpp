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
    LoadNextBlock(str, currentBlock);
    if(type(currentBlock) == title) cout << endl << "IS TITLE!" << endl;
    mChildren.push_back(new Title(currentBlock));

    while(!str.eof()){
        currentBlock.clear();
        LoadNextBlock(str, currentBlock);
        cout << "#### PROCESSING BLOCK: " << endl << currentBlock << endl << "####" << endl;
        if(type(currentBlock) == title){
            mChildren.push_back(new Title(currentBlock.substr(2, currentBlock.size())));
        }
        else if(mChildren.empty()){
            throw new runtime_error("Document does not start with a title!");
        }
        else if(type(currentBlock) == chapter){
            mChildren.back()->mChildren.push_back(new Chapter(currentBlock.substr(3, currentBlock.size())));
        }
        else if(!mChildren.back()->HasChapter()){
            mChildren.back()->mChildren.push_back(new Paragraph(currentBlock));
        }else{
            mChildren.back()->mChildren.back()->mChildren.push_back(new Paragraph(currentBlock));
        }
    }
}

//Loads the next block of text between two empty lines into 'block'
void Component::LoadNextBlock(ifstream & stream, string & block){
    string currentLine;
    while(!stream.eof() && currentLine.empty()){
        cout << "Line: " << currentLine << endl;
        getline(stream, currentLine);
    }

    while(!stream.eof() && !currentLine.empty()){
        cout << "Line: " << currentLine << endl;
        block.append(currentLine).append("\n");
        getline(stream, currentLine);
    }

    block = block.substr(0, block.size()-1);
}

bool Component::HasChapter(){
    for(vector<Component*>::iterator it = mChildren.begin(); it != mChildren.end(); ++it){
        if((*it)->compType == chapter) return true;
    }
    return false;
}

Component::CompType Component::type(string s){
    if(!s.substr(0, 2).compare("==")) return chapter;
    else if(!s.substr(0, 1).compare("=")) return title;
    else return paragraph;
}

void Component::accept(HTMLVisitor * v){}
