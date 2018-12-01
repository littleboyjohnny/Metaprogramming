#pragma once

#include "TypeList.hpp"
#include "TypeListMethods.hpp"

struct EmptyType {};

template<class TL, template<class AtomicType, class Base> class Unit, class Root = EmptyType>
class GenLinearHierarchy;

template< typename TL,
        template<class> class UnitScatter,
        template<class, class> class UnitLinear,
        unsigned int prev_fib = 0, unsigned int curr_fibb = 1 >
class GenScatterHierarchy;

template< typename ...T,
        template<class> class UnitScatter,
        template<class, class> class UnitLinear,
        unsigned int prev_fib, unsigned int curr_fibb >
class GenScatterHierarchy< TypeList<T...>, UnitScatter, UnitLinear, prev_fib, curr_fibb > :
        public GenLinearHierarchy< typename GetFirstN<curr_fibb + 1, TypeList<T...>>::headN, UnitLinear, EmptyType >,
        public GenScatterHierarchy< DeleteFirstN<curr_fibb + 1, TypeList<T...>>,
            UnitScatter, UnitLinear,
            curr_fibb, prev_fib + curr_fibb >
{
};

template< typename AtomicType,
        template<class> class UnitScatter,
        template<class, class> class UnitLinear,
        unsigned int prev_fib, unsigned int curr_fibb >
class GenScatterHierarchy : public UnitScatter<AtomicType>
{
};

template< template<class> class UnitScatter, template<class, class> class UnitLinear>
class GenScatterHierarchy<EmptyTypeList, UnitScatter, UnitLinear>
{
};





template<typename T1, typename ...T2, template<class, class> class Unit, class Root>
class GenLinearHierarchy<TypeList<T1, T2...>, Unit, Root> :
        public Unit<T1, GenLinearHierarchy<TypeList<T2...>, Unit, Root>>
{
};

template<typename T, template<class, class> class Unit, class Root>
class GenLinearHierarchy : public Unit<T, Root>
{
};