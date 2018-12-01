#include <iostream>

#include "Hierarchy.hpp"

template<typename T>
struct Holder : T
{
};

template<typename T, typename Base>
struct HolderL : Base
{
};

class test1 {
};

class test2 {
};

class test3 {
};

using TL = TypeList<test1, test2, test3>;

class Root : public GenScatterHierarchy<TL, Holder, HolderL> {

};


int main() {
    Root r;
    std::cout << sizeof(r) << std::endl;
    return 0;
}