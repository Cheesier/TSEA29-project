#include "message.h"
#include <iostream>

#include <string.h>

Message::Message() {}

Message::Message(const Type_t& type_, const string& data_):
  type(type_),data(data_), created_at(hr_clock::now()){}

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
  printf("----\ntype: %d; size: %lu;\n----\n",int(type), raw_data.size());
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

template<typename... Ts>
void Message::make(const Type_t& type_, const Ts&... args){
  type = type_;
  data.clear();
  make_args(args...);
}

template<typename T, typename... Ts>
void Message::make_args(const T& var, const Ts&...args){
  size_t offset = data.size();
  data.resize(offset+sizeof(var));
  memcpy(&data[offset],(char*)&var, sizeof(var));
  make_args(args...);
}

void Message::make_args(){
  Size_t size = get_data_size();
  raw_data.resize(sizeof(type) + sizeof(Size_t) + data.size());
  memcpy(&raw_data[0],(char*)&type,sizeof(type));
  memcpy(&raw_data[sizeof(type)],(char*)&size,sizeof(size));
  memcpy(&raw_data[sizeof(type) + sizeof(size)],&data[0],data.size());
}

void Message::echo(){
  make(T_ECHO);
}

void Message::go_forward(){
  make(T_GO_FORWARD);
}

void Message::go_backward(){
  make(T_GO_BACKWARD);
}

void Message::turn_right(){
  make(T_TURN_RIGHT);
}

void Message::turn_left(){
  make(T_TURN_LEFT);
}

void Message::go_forward_right(){
  make(T_GO_FORWARD_RIGHT);
}

void Message::go_forward_left(){
  make(T_GO_FORWARD_LEFT);
}

void Message::set_speed(int speed){
  make(T_SET_SPEED,speed);
}

void Message::set_degrees(int degrees){
  make(T_ALERT_AT_DEGREES,degrees);
}

void Message::stop(){
  make(T_STOP);
}

void Message::open_claw(){
  make(T_OPEN_CLAW);
}

void Message::close_claw(){
  make(T_CLOSE_CLAW);
}

void Message::change_direction(int direction){
  make(T_CHANGE_DIRECTION, direction);
}

void Message::change_drive_mode(int dm){
  make(T_CHANGE_DRIVE_MODE, dm);
}

void Message::set_pd(int p, int d){
  make(T_SET_PD,p,d);
}

void Message::go_forward_pd(){
  make(T_GO_FORWARD_PD);
}

void Message::calibrate_black(){
  make(T_CALIBRATE_BLACK);
}

void Message::calibrate_white(){
  make(T_CALIBRATE_WHITE);
}
