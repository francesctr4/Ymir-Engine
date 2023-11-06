#pragma once

#include <iostream>
#include <random>

class RandomNumber {
public:
    RandomNumber() : m_randomEngine(std::random_device{}()) {}

    int generate();

private:
    std::mt19937 m_randomEngine;
};