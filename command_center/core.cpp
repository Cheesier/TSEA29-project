#include "core.h"

Core_ptr core;

Core::Core() {
    printf("creating core..\n");
    w = Gui_ptr(new Gui);
    w->show();
}

Core::~Core() {
  cout << "destroying core.." << endl;
}

// ---------- bluetooth related --------

void Core::bt_connected(){
  printf("bluetooth link is established\n");
  bt_is_connected = true;
}

void Core::bt_disconnected(){
  printf("** bluetooth link is closed\n");
  bt_is_connected = false;
  w->bt_reset_socket();
}

bool Core::get_bt_is_connected(){
    return bt_is_connected;
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
    w->bt_send(msg);
}


void Core::echo(){
    printf("sending echo msg..");
    Msg_ptr msg(new Message);
    msg->echo();
    w->bt_send(msg);
}

void Core::go_forward(){
    printf("sending go forward msg..");
    Msg_ptr msg(new Message);
    msg->go_forward();
    w->bt_send(msg);
}

void Core::go_backward(){
    printf("sending go backward msg..");
    Msg_ptr msg(new Message);
    msg->go_backward();
    w->bt_send(msg);
}

void Core::turn_right(){
    printf("sending turn right msg..");
    Msg_ptr msg(new Message);
    msg->turn_right();
    w->bt_send(msg);
}

void Core::turn_left(){
    printf("sending turn left msg..");
    Msg_ptr msg(new Message);
    msg->go_forward();
    w->bt_send(msg);
}

void Core::stop(){
    printf("sending stop msg..");
    Msg_ptr msg(new Message);
    msg->stop();
    w->bt_send(msg);
}
