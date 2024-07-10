#ifndef VELOCITY_MSG_HPP
#define VELOCITY_MSG_HPP

#include <string>
#include <ctime>
#include <msgpack.hpp>
#include "header.hpp"

struct Velocity_t 
{
    double vx, vy, vtheta;
    MSGPACK_DEFINE(vx, vy, vtheta)
};
#endif
