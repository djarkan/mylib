#ifndef __TRIPLE__
#define __TRIPLE__

namespace mylib
{

template <typename T, typename U,typename V>
class Triple
{

   public:
        Triple();
        Triple(T first, U second, V third);
        Triple(Triple<T, U, V>& triple);

        void                                            swap(Triple<T, U, V>& triple1, Triple<T, U, V>& triple2);

        T first;
        U second;
        V third;
};

#include "triple.inl"

}

#endif // __TRIPLE__

