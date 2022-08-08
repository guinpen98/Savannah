#ifndef SAVANNAH_RAND_H
#define SAVANNAH_RAND_H

#include<random>
#include "configuration.h"

namespace Savannah {
    //êAï®ÉNÉâÉX
    class Rand {
        std::random_device rd;
        std::mt19937 eng;
        std::uniform_int_distribution<> wDistr;
        std::uniform_int_distribution<> hDistr;
        std::bernoulli_distribution uid;

    public:
        explicit Rand() :eng(rd()),wDistr(MIN,wMAX),hDistr(MIN,hMAX),uid(0.01) {}
        struct Vec2 randDist();
    };
}


#endif // !SAVANNAH_RAND_H