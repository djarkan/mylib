#ifndef    __RANDOM_HPP__
#define    __RANDOM_HPP__

#include <random>
#include <algorithm>
#include <chrono>

namespace mylib {

template <typename Type>
class Random {
    public:
        #if defined(__MINGW32__)
            long long int seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::seed_seq sseq{seed};
            std::mt19937 m_gen{sseq};
        #else
           std::random_device rd;
           std::mt19937 m_gen{rd()};
       #endif

       Type randomNumber(Type min, Type max);
       Type randomRealNumber(Type min, Type max);
       std::mt19937 getUniformGenerator();

};
#endif

template <typename Type>
Type Random<Type>::randomNumber(Type min, Type max)
{
    std::uniform_int_distribution<> dis(min, max);
    return dis(m_gen);
}

template <typename Type>
Type Random<Type>::randomRealNumber(Type min, Type max)
{
    std::uniform_real_distribution<> dis(min, max);
    return dis(m_gen);
}

template <typename Type>
std::mt19937 Random<Type>::getUniformGenerator()
{
    return m_gen;

}

}
