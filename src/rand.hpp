#pragma once
#include <random>

std::random_device dev{};
std::mt19937 rng{ dev() };