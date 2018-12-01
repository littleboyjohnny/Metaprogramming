#pragma once


struct Void {};

template <typename ...Args>
struct TypeList {
    typedef Void Head;
    typedef Void Tail;
};


template <typename H, typename ...T>
struct TypeList<H, T...> {
    typedef H Head;
    typedef TypeList<T...> Tail;
};

typedef TypeList<> EmptyTypeList;