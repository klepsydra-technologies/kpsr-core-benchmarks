#ifndef SERIALIZATIONBENCHMARKUTILS_H
#define SERIALIZATIONBENCHMARKUTILS_H

#include <iostream>
#include <limits>
#include <random>

class SerializationBenchmarkUtils 
{
public:
    static float getRandomFloatUsingWholeRange()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        return std::uniform_real_distribution<float>(
            std::numeric_limits<float>::max(), std::numeric_limits<float>::min())(gen);
    }
};

#endif // SERIALIZATIONBENCHMARKUTILS_H