#ifndef MESSAGE_H
#define MESSAGE_H

#include<string>
#include<memory>
#include<ctime>
#include<cstring>

#include "glob.h"

class Message;
typedef shared_ptr<Message> Msg_ptr;

class Message {
public:
  typedef unsigned char Size_t;
  typedef unsigned char Type_t;

  Message(){}
  Message(const Type_t& type_, const string& data_);
  enum msg_t{t_echo, t_go_forward, t_go_backward, t_turn_right, t_turn_left, t_stop};

  Type_t get_type();
  string get_data();
  time_t get_timestamp();
  size_t get_data_size();
  char * get_raw_data();
  size_t get_raw_data_size();

  void print();
  void encode();

  //constructors

  void echo();
  void go_forward();
  void go_backward();
  void turn_right();
  void turn_left();
  void stop();

private:

  Type_t type;
  string data;
  // FIXME : good anough? -- maybe need milliseconds instead
  time_t timestamp;

  string raw_data;
};

#endif // MESSAGE_H
