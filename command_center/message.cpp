#include "message.h"
#include <iostream>

Message::Message(const Type_t& type_, const string& data_):
  type(type_), data(move(data_)), created_at(hr_clock::now()){}

Message::Type_t Message::get_type() const{
  return type;
}

string Message::get_data() const{
  return data;
}

hr_clock::time_point Message::get_created_at() const{
  return created_at;
}

Message::Size_t Message::get_data_size() const{
  return data.size();
}

void Message::print(){
  printf("type: %d; size:%lu;%s\n----\n",int(type), data.size(), data.c_str());
}

void Message::encode(){
  Size_t size(data.size());
#ifdef TEXTMODE
  type+='0';
  size+='0';
#endif
  raw_data.resize(sizeof(type) + sizeof(size) + data.length());
  char* offset = &raw_data[0];
  memcpy(offset,&type,sizeof(type));
  offset+=sizeof(type);
  memcpy(offset,&size,sizeof(size));
  offset+=sizeof(size);
  memcpy(offset,&data[0],data.length());
}

char* Message::get_raw_data(){
  return &raw_data[0];
}

size_t Message::get_raw_data_size(){
  return raw_data.size();
}

// ----------- operators -----

ostream& operator << (ostream& os, const Message& msg){
  //int64_t timestamp = hr_clock::to msg.created_at;
  const auto & duration  = chrono::nanoseconds(msg.get_created_at().time_since_epoch());
  const uint64_t& timestamp = chrono::duration_cast<chrono::nanoseconds>(duration).count();
  const Message::Type_t& type = msg.get_type();
  const Message::Size_t& size = msg.get_data_size();
  const string& data = msg.get_data();
  os.write((char*)&timestamp,sizeof(timestamp));
  os.write((char*)&type, sizeof(type));
  os.write((char*)&size, sizeof(size));
  os.write(data.data(),size);

  return os;
}

istream& operator >> (istream& is, Message& msg){
  uint64_t timestamp;
  is.read((char*)&timestamp, sizeof(timestamp));
  const auto& duration = chrono::nanoseconds(timestamp);
  msg.created_at = hr_clock::time_point(duration);

  is.read((char*)&msg.type, sizeof(msg.type));
  Message::Size_t size;
  is.read((char*)&size, sizeof(size));
  msg.data.resize(size);
  is.read((char*)msg.data.data(),size);
  return is;
}


// ------------ constructors ----------
// do not forget to encode

void Message::echo(){
  type = T_ECHO;
  data = "echo msg";
  encode();
}

void Message::go_forward(){
  type = T_GO_FORWARD;
  data.clear();
  encode();
}

void Message::go_backward(){
  type = T_GO_BACKWARD;
  data.clear();
  encode();
}

void Message::turn_right(){
  type = T_TURN_RIGHT;
  data.clear();
  encode();
}

void Message::turn_left(){
  type = T_TURN_LEFT;
  data.clear();
  encode();
}

void Message::go_forward_right(){
  type = T_GO_FORWARD_RIGHT;
  data.clear();
  encode();
}

void Message::go_forward_left(){
  type = T_GO_FORWARD_LEFT;
  data.clear();
  encode();
}

void Message::stop(){
  type = T_STOP;
  data.clear();
  encode();
}

//TODO: set actual value later
void Message::set_p(const double &val){
  type = T_P;
  data.clear();
  encode();
}

void Message::set_d(const double &val){
  type = T_D;
  data.clear();
  encode();
}


