#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/Receiver.hpp>
#include <webots/Connector.hpp>

#include "base.h"
#include "msg/velocity_msg.hpp"
#include "msg/solenoid_msg.hpp"
#include <icecream.hpp>

// All the webots classes are defined in the "webots" namespace

using namespace webots;

double vx_;
double vy_;
double vtheta_;

std::unique_ptr<Base> Base::instance = nullptr;
std::once_flag Base::initInstanceFlag;
int main(int argc, char **argv)
{
  // create the Robot instance.
  Robot *robot = new Robot();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();

  Receiver *receiver = new Receiver("receiver");
  receiver->enable(timeStep);

  Connector *front_active_connector = new Connector("front_active_connector");
  Connector *back_active_connector = new Connector("back_active_connector");

  front_active_connector->enablePresence(timeStep);
  back_active_connector->enablePresence(timeStep);

  Motor *m_fl = robot->getMotor("m_fl");
  Motor *m_fr = robot->getMotor("m_fr");
  Motor *m_rl = robot->getMotor("m_rl");
  Motor *m_rr = robot->getMotor("m_rr");

  icecream::ic.prefix("slave_2 | ");
  Base &base_ = Base::getInstance();
  base_.init_motor(m_fl, m_fr, m_rl, m_rr);

  bool front_unlock = false;
  bool back_unlock = false;

  while (robot->step(timeStep) != -1)
  {
    if (receiver->getQueueLength() > 0)
    {
      const void *data = receiver->getData();
      size_t dataSize = receiver->getDataSize();


      Header_t header;
      msgpack::object_handle msg = msgpack::unpack((const char *)data, dataSize);
      msgpack::object deserialized = msg.get();
      deserialized.convert(header);

      std::string topic = header.topic;

      msgpack::object_handle oh = msgpack::unpack(header.data.data(), header.data.size());
      msgpack::object data_des = oh.get();

      if (topic == "sl_set")
      {
        SolenoidSet_t sl_set;
        data_des.convert(sl_set);
        if (sl_set.number == 0)
          front_unlock = sl_set.state;
        else if (sl_set.number == 1)
          back_unlock = sl_set.state;
      }
      else if (topic == "vel_set")
      {
        Velocity_t velocityMsg;
        data_des.convert(velocityMsg);
        vx_ = velocityMsg.vx;
        vy_ = velocityMsg.vy;
        vtheta_ = velocityMsg.vtheta;
      }
      else
      {
        std::cout << "Unknown topic received: " << topic << std::endl;
      }

      receiver->nextPacket();
    }

    base_.base_move(vx_, vy_, vtheta_);

    if (front_unlock)
      front_active_connector->unlock();
    if (not front_active_connector->getPresence())
      front_unlock = false;

    if (front_active_connector->getPresence() and not front_active_connector->isLocked() and not front_unlock)
    {
      front_active_connector->lock();
    }

    if (back_unlock)
      back_active_connector->unlock();
    if (not back_active_connector->getPresence())
      back_unlock = false;

    if (back_active_connector->getPresence() and not back_active_connector->isLocked() and not back_unlock)
    {
      back_active_connector->lock();
    }
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
