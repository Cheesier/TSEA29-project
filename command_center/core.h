#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <memory>
#include <deque>
#include <thread>
#include <mutex>

#include "glob.h"
#include "gui.h"
#include "message.h"
#include "btinterface.h"

class Core;
typedef unique_ptr<Core> Core_ptr;

class Gui;
typedef unique_ptr<Gui> Gui_ptr;

class BTInterface;
typedef unique_ptr<BTInterface> BTInterface_ptr;

extern Core_ptr core;

class Core {
public:
  Core();
  ~Core();

  void init();

  //bluetooth related
  void bt_avaible();
  void bt_connect();
  void bt_disconnect();
  void bt_connected();
  void bt_disconnected();

  bool bt_is_connected();

  void process_msg(const Msg_ptr& msg);

  // bluetooth commands
  void echo();
  void go_forward();
  void go_backward();
  void turn_right();
  void turn_left();
  void stop();

private:

  //handle new msgs
  void handle_echo(const Msg_ptr& msg);
  void handle_unknown(const Msg_ptr& msg);

  //write
  void send(const Msg_ptr& msg);

//data
  Gui_ptr w;
  BTInterface_ptr bt;
};

#endif // CORE_H
