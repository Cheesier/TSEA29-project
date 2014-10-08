#include "core.h"

Core_ptr core;

Core::Core() {
  printf("creating core..\n");
#ifdef LINUX
  printf("running on linux\n");
#endif
}

Core::~Core() {
  cout << "destroying core.." << endl;
  //Something wierd, neet to call destructor manually
  w.reset();
}

void Core::init(){
  printf("initializing core..\n");
  w.reset(new Gui);
  w->show();
  bt.reset(new BTInterface);
}

// ---------- bluetooth related --------

void Core::bt_avaible(){
  printf("found local bluetooth device\n");
  w->bt_reset();
}

void Core::bt_connect(){
  bt->connect_to_device(REMOTE_DEVICE_ADDRESS);
  w->bt_connecting();
}

void Core::bt_disconnect(){
    bt->disconnect();
    w->bt_reset();
}

void Core::bt_connected(){
  printf("bluetooth link is established\n");
  w->bt_connected();
}

void Core::bt_disconnected(){
  printf("** bluetooth link is closed\n");
  w->bt_reset();
}

bool Core::bt_is_connected(){
    return bt->is_connected();
}

// --------- comm --------------

void Core::process_msg(const Msg_ptr &msg){
  thread t([this, msg](){
    switch(msg->get_type()){
    case Message::t_echo:
      handle_echo(msg);
      break;
    default:
      handle_unknown(msg);
    }
  });
  t.detach();
}

void Core::handle_echo(const Msg_ptr &msg){
  msg->print();
}

void Core::handle_unknown(const Msg_ptr &msg){
  printf("unknown message:\n");
  msg->print();
}

// ------------- bluetooth commands -----------

void Core::send(const Msg_ptr &msg){
  printf("sending new msg..\n");
  bt->send(msg);
}

void Core::echo(){
  Msg_ptr msg(new Message);
  msg->echo();
  send(msg);
}

void Core::go_forward(){
  Msg_ptr msg(new Message);
  msg->go_forward();
  send(msg);
}

void Core::go_backward(){
  Msg_ptr msg(new Message);
  msg->go_backward();
  send(msg);
}

void Core::turn_right(){
  Msg_ptr msg(new Message);
  msg->turn_right();
  send(msg);
}

void Core::turn_left(){
  Msg_ptr msg(new Message);
  msg->go_forward();
  send(msg);
}

void Core::stop(){
  Msg_ptr msg(new Message);
  msg->stop();
  send(msg);
}
