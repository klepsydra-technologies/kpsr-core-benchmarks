#ifndef VECTORFLOATSTRUCT4PODS_H
#define VECTORFLOATSTRUCT4PODS_H

#pragma once
#include <SerializationBenchmarkUtils.h>
#include <VectorFloatStruct.h>
#include <iostream>
#include <pods/pods.h>
#include <pods/binary.h>
#include <pods/json.h>
#include <pods/buffers.h>



struct VectorFloatStruct4Pods : public VectorFloatStruct 
{
    VectorFloatStruct4Pods() : VectorFloatStruct() {};
    VectorFloatStruct4Pods(long l_size_vec) : VectorFloatStruct(l_size_vec) {};
    VectorFloatStruct4Pods(long l_size_vec, float initFloatValue) : VectorFloatStruct(l_size_vec, initFloatValue) {};

    PODS_SERIALIZABLE(
        1,
        PODS_MDR(_vec_f))
};
#endif
