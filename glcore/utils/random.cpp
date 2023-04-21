//
// Created by shepherd on 21.4.23.
//

#include <glcore/utils/random.hpp>

namespace glcore {

std::random_device Random::device_;
std::mt19937 Random::generator_;
std::uniform_int_distribution<std::mt19937::result_type> Random::distribution_;

void Random::Init() {
    generator_.seed(device_());
}

float Random::Get() {
    return (float) distribution_(generator_) / std::numeric_limits<uint64_t>::max();
}

} // glcore