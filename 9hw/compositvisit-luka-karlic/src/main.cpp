#include <iostream>
#include "composite.h"

using namespace std;

int main(int argc, char * argv[])
{
    std::string file = "text1.txt";
    if(argc > 1) 
        file = argv[1];


    ifstream in(file);
    if(!in)
        throw std::runtime_error("Cannot open file " + file + ".\n");
    Component document;
    document.read(in);
    in.close();
    HTMLVisitor html;
    document.accept(&html);
    std::cout << html.getResult() << std::endl;  

    return 0;
}
