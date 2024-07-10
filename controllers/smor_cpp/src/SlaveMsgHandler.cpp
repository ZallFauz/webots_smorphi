#include "SlaveMsgHandler.hpp"
#include "icecream.hpp"
SlaveMsgHandler::SlaveMsgHandler(webots::Emitter *emitter1,
                                 webots::Emitter *emitter2,
                                 webots::Emitter *emitter3,
                                 webots::Receiver *receiver1,
                                 webots::Receiver *receiver2,
                                 webots::Receiver *receiver3)
    : emitter1_(emitter1),
      emitter2_(emitter2),
      emitter3_(emitter3),
      receiver1_(receiver1),
      receiver2_(receiver2),
      receiver3_(receiver3)
{
}

void SlaveMsgHandler::update()
{
    readSlave(receiver1_, this->slave1_);
    readSlave(receiver2_, this->slave2_);
    readSlave(receiver3_, this->slave3_);
}

Slave SlaveMsgHandler::slave1() const
{
    return this->slave1_;
}

Slave SlaveMsgHandler::slave2() const
{
    return this->slave2_;
}

Slave SlaveMsgHandler::slave3() const
{
    return this->slave3_;
}

void SlaveMsgHandler::slave_set_solenoid(int module_num, const std::string &side, int state)
{
    if (module_num < 1 or module_num > 3)
    {
        std::cout << "module out of range\n";
        return;
    }
    SolenoidSet_t solenoidMessage;
    solenoidMessage.side = side;
    solenoidMessage.state = state;

    msgpack::sbuffer solenoidBuffer;
    msgpack::pack(solenoidBuffer, solenoidMessage);

    std::string serialized;
    serialized.assign(solenoidBuffer.data(), solenoidBuffer.size());
    webots::Emitter *emitter;
    switch (module_num)
    {
    case 1:
        emitter = emitter1_;
        break;

    case 2:
        emitter = emitter2_;
        break;
    case 3:
        emitter = emitter3_;
        break;
    default:
        break;
    }
    if (emitter)
        this->send("sl_set", emitter, serialized);
}

void SlaveMsgHandler::slave_set_velocity(int module_num, double vx, double vy, double vtheta)
{
    if (module_num < 1 or module_num > 3)
    {
        std::cout << "module out of range\n";
        return;
    }
    Velocity_t velocityMessage;
    velocityMessage.vx = vx;
    velocityMessage.vy = vy;
    velocityMessage.vtheta = vtheta;

    msgpack::sbuffer velocityBuffer;
    msgpack::pack(velocityBuffer, velocityMessage);

    std::string serialized;
    serialized.assign(velocityBuffer.data(), velocityBuffer.size());

    webots::Emitter *emitter;
    switch (module_num)
    {
    case 1:
        emitter = emitter1_;
        break;

    case 2:
        emitter = emitter2_;
        break;
    case 3:
        emitter = emitter3_;
        break;
    default:
        break;
    }

    if (emitter)
    {
        this->send("vel_set", emitter, serialized);
    }
}

void SlaveMsgHandler::send(const std::string &topic, webots::Emitter *emitter_, const std::string &serialized_data)
{
    Header_t header_;
    header_.topic = topic;
    header_.data = serialized_data;
    msgpack::sbuffer headerBuffer;
    msgpack::pack(headerBuffer, header_);
    emitter_->send(headerBuffer.data(), headerBuffer.size());
}

SlaveMsgHandler::~SlaveMsgHandler()
{
}

void SlaveMsgHandler::readSlave(webots::Receiver *receiver_, Slave &slave)
{
    while (receiver_->getQueueLength() > 0)
    {
        const void *data = receiver_->getData();
        size_t dataSize = receiver_->getDataSize();

        msgpack::object_handle oh = msgpack::unpack((const char *)data, dataSize);
        msgpack::object deserialized = oh.get();

        Header_t header;
        deserialized.convert(header);
        std::string topic = header.topic;

        msgpack::object_handle oh_data = msgpack::unpack(header.data.data(), header.data.size());
        msgpack::object data_des = oh_data.get();

        if (topic == "sl_feedback")
        {
            SolenoidState_t sl_get;
            data_des.convert(sl_get);
            if (sl_get.side == "front")
                slave.sl_front = sl_get.state;
            else if (sl_get.side == "back")
                slave.sl_back = sl_get.state;
            else if (sl_get.side == "right")
                slave.sl_right = sl_get.state;
        }
        else
        {
            std::cout << "Unknown topic received: " << topic << std::endl;
        }

        receiver_->nextPacket();
    }
}
