#pragma once

#include <type_traits>

#include "TypeList.hpp"

template<typename TL>
struct IsEmpty :
        std::true_type
{
};

template<>
struct IsEmpty<EmptyTypeList> :
        std::true_type
{
};

template<typename ...Args>
struct IsEmpty<TypeList<Args...>> :
        std::integral_constant<bool,
                std::is_same<typename TypeList<Args...>::Head, Void>::value &&
                IsEmpty<typename TypeList<Args...>::Tail>::value
            >
{
};

template<typename TL>
struct Length :
        std::integral_constant<unsigned int, 0>
{
};

template<typename ...Args>
struct Length<TypeList<Args...>> :
        std::integral_constant<unsigned int,
            IsEmpty<TypeList<Args...>>::value ?
                0 : 1 + Length<typename TypeList<Args...>::Tail>::value
        >
{
};

template<unsigned int N, typename TL>
struct TypeAt
{
    typedef Void type;
};

template<typename ...Args>
struct TypeAt<0, TypeList<Args...>>
{
    typedef typename TypeList<Args...>::Head type;
};

template<unsigned int N, typename ...Args>
struct TypeAt<N, TypeList<Args...>>
{
    static_assert(N < Length<TypeList<Args...>>::value, "N is out of range");

    typedef typename TypeAt<N - 1, typename TypeList<Args...>::Tail>::type type;
};


template<typename T, typename TL>
struct PushFront;

template<typename T, typename ...Args>
struct PushFront<T, TypeList<Args...>>
{
    typedef TypeList<T, Args...> NewTypeList;
};


template<unsigned int N, typename TL>
struct GetFirstN;

template<typename ...Args>
struct GetFirstN<0, TypeList<Args...>>
{
    typedef EmptyTypeList headN;
};

template<unsigned int N>
struct GetFirstN<N, EmptyTypeList>
{
    typedef EmptyTypeList headN;
};

template<unsigned int N, typename ...Args>
struct GetFirstN<N, TypeList<Args...>>
{
    typedef typename PushFront<typename TypeList<Args...>::Head, typename GetFirstN<N-1,
        typename TypeList<Args...>::Tail>::headN>::NewTypeList headN;
};


template<unsigned int N, typename TL>
struct DeleteFirstN;

template< typename ...Args>
struct DeleteFirstN<0, TypeList<Args...>>
{
    typedef TypeList<Args...> TLWithoutFirstN;
};

template<unsigned int N>
struct DeleteFirstN<N, EmptyTypeList>
{
    typedef EmptyTypeList TLWithoutFirstN;
};

template<unsigned int N, typename ...Args>
struct DeleteFirstN<N, TypeList<Args...>>
{
    typedef typename DeleteFirstN<N-1, typename TypeList<Args...>::Tail>::TLWithoutFirstN TLWithoutFirstN;
};