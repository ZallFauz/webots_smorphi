// File:          smor_cpp.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/Keyboard.hpp>
#include <webots/Emitter.hpp>
#include <webots/Connector.hpp>

#include "msg/velocity_msg.hpp"

#include "SlaveMsgHandler.hpp"
#include "base.h"
#include <icecream.hpp>
// All the webots classes are defined in the "webots" namespace
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node

std::unique_ptr<Base> Base::instance = nullptr;
std::once_flag Base::initInstanceFlag;

int main(int argc, char **argv)
{
  // create the Robot instance.
  Robot *robot = new Robot();
  IC(robot->getName());

  Keyboard *key = new Keyboard();

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();
  key->enable(timeStep);

  Emitter *emitter1 = new Emitter("emitter1");
  Emitter *emitter2 = new Emitter("emitter2");
  Emitter *emitter3 = new Emitter("emitter3");

  Receiver *receiver1 = new Receiver("receiver_slave_1");
  receiver1->enable(timeStep);
  Receiver *receiver2 = new Receiver("receiver_slave_2");
  receiver2->enable(timeStep);
  Receiver *receiver3 = new Receiver("receiver_slave_3");
  receiver3->enable(timeStep);

  SlaveMsgHandler *slave_msg_handler = new SlaveMsgHandler(emitter1, emitter2, emitter3, receiver1, receiver2, receiver3);

  Connector *left_active_connector = new Connector("left_active_connector");
  left_active_connector->enablePresence(timeStep);

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  Motor *m_fl = robot->getMotor("m_fl");
  Motor *m_fr = robot->getMotor("m_fr");
  Motor *m_rl = robot->getMotor("m_rl");
  Motor *m_rr = robot->getMotor("m_rr");

  icecream::ic.prefix("master | ");
  Base &base_ = Base::getInstance();
  base_.init_motor(m_fl, m_fr, m_rl, m_rr);

  int last_key = -1;

  Velocity_t vel;
  vel.vx = 0;
  vel.vy = 0;
  vel.vtheta = 0;
  // IC();
  bool unlock = false;
  while (robot->step(timeStep) != -1)
  {
    slave_msg_handler->update();

    auto k = key->getKey();
    if (k >= 0 and k != last_key)
    {
      if (k == key->UP)
      {
        // base_.base_forwards_increment();
        vel.vx += 0.05;
      }
      else if (k == key->LEFT)
      {
        base_.base_strafe_left_increment();
      }
      else if (k == key->RIGHT)
      {
        base_.base_strafe_right_increment();
      }
      else if (k == key->DOWN)
      {
        // base_.base_backwards_increment();
        vel.vx -= 0.05;
      }
      else if (k == key->PAGEDOWN)
      {
        // base_.base_turn_right_increment();
        auto r = sqrt(0.205 * 0.205);
        auto vtheta = -0.3; // rad/s
        auto vlin = r * vtheta;
        // IC(vlin);

        auto angle = atan2(-0.205, 0.205);
        // IC(angle);
        auto vx = vlin * cos(angle);
        auto vy = vlin * -sin(angle);

        // IC(vx, vy);
        vel.vx = vx;
        vel.vy = vy;
        vel.vtheta = vtheta;
      }
      else if (k == key->PAGEUP)
      {
        // base_.base_turn_left_increment();
        auto r = sqrt(0.205 * 0.205);
        auto vtheta = 0.3; // rad/s
        auto vlin = r * vtheta;
        // IC(vlin);

        auto angle = atan2(-0.205, 0.205);
        // IC(angle);
        auto vx = vlin * cos(angle);
        auto vy = vlin * -sin(angle);

        // IC(vx, vy);
        vel.vx = vx;
        vel.vy = vy;
        vel.vtheta = vtheta;
      }
      else if (k == ' ')
      {
        base_.base_reset();
        vel.vtheta = 0;
        vel.vx = 0;
        vel.vy = 0;
        unlock = true;
        slave_msg_handler->slave_set_solenoid(1, "front", 1);
        slave_msg_handler->slave_set_solenoid(1, "back", 1);
        slave_msg_handler->slave_set_solenoid(2, "front", 1);
        slave_msg_handler->slave_set_solenoid(2, "back", 1);
        slave_msg_handler->slave_set_solenoid(3, "right", 1);
      }
    }

    slave_msg_handler->slave_set_velocity(1, vel.vx, vel.vy, vel.vtheta);
    slave_msg_handler->slave_set_velocity(2, vel.vx, vel.vy, vel.vtheta);
    slave_msg_handler->slave_set_velocity(3, vel.vx, vel.vy, vel.vtheta);

    if (unlock)
    {
      left_active_connector->unlock();
    }
    if (not left_active_connector->getPresence())
      unlock = false;
    // IC(left_active_connector->getPresence(), left_active_connector->isLocked());

    if (left_active_connector->getPresence() and not left_active_connector->isLocked() and not unlock)
    {
      left_active_connector->lock();
    }

    last_key = k;
    // Enter here functions to send actuator commands, like:
    // m_fl->setVelocity(-5);
    // m_fr->setVelocity(5);
    // m_rl->setVelocity(5);
    // m_rr->setVelocity(-5);
  };

  // Enter here exit cleanup code.
  IC();
  delete robot;
  return 0;
}
