#include "Component.h"
#include "HTMLVisitor.h"
#include <iostream>
#include <stdexcept>
using namespace std;

int main()
{
    Component document;

    ifstream in("tekst.txt");

    if(!in) throw std::runtime_error("Canot open file tekst.txt.\n");

    document.read(in);

    in.close();

    //print file
    document.accept(new HTMLVisitor());
    document.print();

    return 0;
}
