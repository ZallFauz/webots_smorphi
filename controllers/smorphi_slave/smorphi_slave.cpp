#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/Emitter.hpp>
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

  Emitter *emitter = new Emitter("emitter");

  Connector *front_active_connector;
  Connector *back_active_connector;
  Connector *right_active_connector;

  if (robot->getName() == "slave_1" or robot->getName() == "slave_2")
  {
    front_active_connector = new Connector("front_active_connector");
    back_active_connector = new Connector("back_active_connector");

    front_active_connector->enablePresence(timeStep);
    back_active_connector->enablePresence(timeStep);
  }
  else if (robot->getName() == "slave_3")
  {
    right_active_connector = new Connector("right_active_connector");
    right_active_connector->enablePresence(timeStep);
  }

  Motor *m_fl = robot->getMotor("m_fl");
  Motor *m_fr = robot->getMotor("m_fr");
  Motor *m_rl = robot->getMotor("m_rl");
  Motor *m_rr = robot->getMotor("m_rr");

  icecream::ic.prefix(robot->getName() + " | ");
  Base &base_ = Base::getInstance();
  base_.init_motor(m_fl, m_fr, m_rl, m_rr);

  bool front_unlock = false;
  bool back_unlock = false;
  bool right_unlock = false;

  if (robot->getName() != "slave_3")
    icecream::ic.disable();

  while (robot->step(timeStep) != -1)
  {
    while (receiver->getQueueLength() > 0)
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
        if (sl_set.side == "front")
          front_unlock = sl_set.state;
        else if (sl_set.side == "back")
          back_unlock = sl_set.state;
        else if (sl_set.side == "right")
          right_unlock = sl_set.state;
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

    if (robot->getName() == "slave_1" or robot->getName() == "slave_2")
    {
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

      SolenoidState_t sl_state;
      sl_state.side = "front";
      sl_state.state = front_active_connector->isLocked();

      Header_t header;
      msgpack::sbuffer sl_buffer;
      msgpack::pack(sl_buffer, sl_state);
      header.topic = "sl_feedback";
      header.data.assign(sl_buffer.data(), sl_buffer.size());

      msgpack::sbuffer header_buffer;
      msgpack::pack(header_buffer, header);
      emitter->send(header_buffer.data(), header_buffer.size());

      sl_state.side = "back";
      sl_state.state = back_active_connector->isLocked();
      msgpack::pack(sl_buffer, sl_state);
      header.data.assign(sl_buffer.data(), sl_buffer.size());

      msgpack::pack(header_buffer, header);
      emitter->send(header_buffer.data(), header_buffer.size());
    }
    else if (robot->getName() == "slave_3")
    {

      if (right_unlock)
        right_active_connector->unlock();
      if (not right_active_connector->getPresence())
        right_unlock = false;

      if (right_active_connector->getPresence() and not right_active_connector->isLocked() and not right_unlock)
      {
        right_active_connector->lock();
      }
    }
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
