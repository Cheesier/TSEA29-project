#ifndef MESSAGE_H
#define MESSAGE_H

#include<string>
#include<memory>
#include<ctime>
#include<cstring>
#include<chrono>
#include<fstream>

#include "glob.h"

class Message;
typedef shared_ptr<Message> Msg_ptr;

typedef chrono::high_resolution_clock hr_clock;

class Message {
public:
  typedef unsigned char Size_t;
  typedef unsigned char Type_t;

  Message(){}
  Message(const Type_t& type_, const string& data_);
  enum msg_t{T_ECHO, T_GO_FORWARD, T_GO_BACKWARD, T_TURN_RIGHT, T_TURN_LEFT, T_GO_FORWARD_RIGHT, T_GO_FORWARD_LEFT, T_STOP, T_P, T_D};

  inline bool operator> (const Message& other) {return created_at > other.created_at;}
  inline bool operator< (const Message& other) {return created_at < other.created_at;}

  friend ostream& operator << (ostream& os, const Message& msg);
  friend istream& operator >> (istream& os, Message& msg);

  Type_t get_type() const;
  string get_data() const;
  hr_clock::time_point get_created_at()const;
  Size_t get_data_size() const;
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
  void go_forward_right();
  void go_forward_left();
  void stop();

  void set_p(const double& val);
  void set_d(const double& val);


private:

  Type_t type;
  string data;
  hr_clock::time_point created_at;

  string raw_data;
};

#endif // MESSAGE_H
