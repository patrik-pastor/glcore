//
// Created by shepherd on 21.4.23.
//

#ifndef GLCORE_RANDOM_HPP
#define GLCORE_RANDOM_HPP

#include <random>

namespace glcore {

// https://stackoverflow.com/questions/5019393/random-number-generator-c
class Random {
public:
    static void Init();

    static float Get();

private:
    static std::random_device device_;
    static std::mt19937 generator_;
    // https://stackoverflow.com/questions/32860654/what-are-the-advantages-of-using-uniform-int-distribution-vs-a-modulus-operation
    static std::uniform_int_distribution<std::mt19937::result_type> distribution_;
};

} // glcore

#endif //GLCORE_RANDOM_HPP
