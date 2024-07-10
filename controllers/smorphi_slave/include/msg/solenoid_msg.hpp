#ifndef SOLENOID_HPP
#define SOLENOID_HPP

#include "header.hpp"

struct SolenoidSet_t
{
    std::string side;
    int state;
    MSGPACK_DEFINE(side, state)
};

struct SolenoidState_t
{
    std::string side;
    int state;
    MSGPACK_DEFINE(side, state)
};

#endif