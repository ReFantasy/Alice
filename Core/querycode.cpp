#include "querycode.h"

QueryCode::QueryCode()
{

}

unsigned int RandomUInt()
{
    std::random_device device;
    std::mt19937_64 rng(device());
    return rng();
}