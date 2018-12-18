#include <iostream>

#include "TypeList.hpp"
#include "TypeListMethods.hpp"
#include "Reader.hpp"

using TL = TypeList<int, int, double>;

int main() {
    std::string filename = "/home/kozlov-as/CLionProjects/MetaTask3/text.txt";
    Reader<TL>* reader = new Reader<TL>(filename);
    void* mem = reader->readNextLine();
    int a = *(int*)mem;
    mem = (void*)((int*)mem + sizeof(int));
    int b = *(int*)mem;
    mem = (void*)((int*)mem + sizeof(int));
    double c = *(double*)mem;
    mem = (void*)((int*)mem + sizeof(double));
    return 0;
}