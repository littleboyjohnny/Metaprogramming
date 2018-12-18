#pragma once

#include "TypeList.hpp"
#include "TypeListMethods.hpp"

#include <string>
#include <iostream>
#include <fstream>

template<typename TL>
class Reader;

template<typename TL>
class Helper;

template<typename ...Args>
class Helper<TypeList<Args...>>  {
    using head = typename TypeList<Args...>::Head;

    using tail = typename TypeList<Args...>::Tail;

public:
    Helper(void* mem, std::ifstream& fs) {
        head a;
        fs >> a;
        *((head*)mem) = a;
        mem = (void*)((int*)mem + sizeof(head));
        Helper<tail> h(mem, fs);
    }
};

template<>
class Helper<EmptyTypeList> {
public:
    Helper(void* mem, std::ifstream& fs){}
};



template<typename ...Args>
class Reader<TypeList<Args...>> {
public:
    explicit Reader(std::string filename) {
        this->file.open(filename.c_str());
        size = SumSize<TypeList<Args...>>::value;
    }

    ~Reader() {
        this->file.close();
    }

    void* readNextLine() {
        void* mem = malloc(size);
        Helper<TypeList<Args...>> h(mem, file);
        return mem;
    }

private:
    std::ifstream file;
    size_t size;
};
