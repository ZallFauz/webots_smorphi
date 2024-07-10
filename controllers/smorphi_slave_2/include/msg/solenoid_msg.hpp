#ifndef SOLENOID_HPP
#define SOLENOID_HPP

#include "header.hpp"

struct SolenoidSet_t
{
    int number;
    int state;
    MSGPACK_DEFINE(number, state)
};

struct SolenoidState_t
{
    int number;
    int state;
    MSGPACK_DEFINE(number, state)
};

#endif