#include "Component.h"
#include "HTMLVisitor.h"
#include <iostream>
#include <stdexcept>
#include "Iterator.h"
using namespace std;

int main()
{
    Component document;

    ifstream in("tekst.txt");

    if(!in) throw std::runtime_error("Canot open file tekst.txt.\n");

    document.read(in);

    in.close();

    //print file
    for(vector<Component*>::iterator it_t = document.mChildren.begin(); it_t != document.mChildren.end(); ++it_t){
        (*it_t)->accept(new HTMLVisitor());
        cout << endl << "TITLE TEXT: " << (*it_t)->text << endl;
        for(vector<Component*>::iterator it_c = (*it_t)->mChildren.begin(); it_c != (*it_t)->mChildren.end(); ++it_c){
            (*it_c)->accept(new HTMLVisitor());
            cout << endl << "CHAPTER TEXT: " << (*it_c)->text << endl;
            for(vector<Component*>::iterator it_p = (*it_c)->mChildren.begin(); it_p != (*it_c)->mChildren.end(); ++it_p){
                (*it_p)->accept(new HTMLVisitor());
                cout << endl << "PARAGRAPH TEXT: " << (*it_p)->text << endl;
            }
        }
    }

//    document.accept(&html);

    return 0;
}
