#ifndef HEADER_HPP
#define HEADER_HPP
#include <msgpack.hpp>
#include <string>

struct Header_t
{
    std::string topic;
    std::string data;


    MSGPACK_DEFINE(topic, data);
};
#endif