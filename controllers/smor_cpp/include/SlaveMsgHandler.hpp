#ifndef SLAVEHANDLER_HPP
#define SLAVEHANDLER_HPP

#include <webots/Emitter.hpp>
#include <webots/Receiver.hpp>
#include <msgpack.hpp>
#include "msg/velocity_msg.hpp"
#include "msg/solenoid_msg.hpp"

#include <iostream>

class Slave
{
public:
    int sl_front = 0;
    int sl_back = 0;
    int sl_right = 0;
};

class SlaveMsgHandler
{
private:
    webots::Emitter *emitter1_;
    webots::Emitter *emitter2_;
    webots::Emitter *emitter3_;

    webots::Receiver *receiver1_;
    webots::Receiver *receiver2_;
    webots::Receiver *receiver3_;

    Slave slave1_;
    Slave slave2_;
    Slave slave3_;

private:
    void readSlave(webots::Receiver *receiver_, Slave &slave);

public:
    SlaveMsgHandler(webots::Emitter *emitter1,
                    webots::Emitter *emitter2,
                    webots::Emitter *emitter3,
                    webots::Receiver *receiver1,
                    webots::Receiver *receiver2,
                    webots::Receiver *receiver3);

    ~SlaveMsgHandler();
    void update();

    Slave slave1() const;
    Slave slave2() const;
    Slave slave3() const;

    void slave_set_solenoid(int module_num, const std::string &side, int state);
    void slave_set_velocity(int module_num, double vx, double vy, double vtheta);
    void send(const std::string &topic, webots::Emitter *emitter_, const std::string &serialized_data);
};

#endif