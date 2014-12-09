#include "message.h"
#include <iostream>

#include <string.h>

Message::Message() {
    data = new QByteArray();
}

Message::Message(const Type_t& type_, const QByteArray* data_):
  type(type_), created_at(hr_clock::now()){
    data = new QByteArray(*data_);
}

Message::Type_t Message::get_type() const{
  return type;
}

char* Message::get_data() const{
  return data->data();
}

hr_clock::time_point Message::get_created_at() const{
  return created_at;
}

Message::Size_t Message::get_data_size() const{
  return data->size();
}

void Message::print(){
  //printf("----\ntype: %d; size: %lu; data: %s;\n----\n",int(type), data->size(), data.c_str());
}

void Message::encode(){
  /*Size_t size(data->size());
#ifdef TEXTMODE
  type+='0';
  size+='0';
#endif
  raw_data->resize(sizeof(type) + sizeof(size) + data->length());
  char* offset = &raw_data[0];
  memcpy(offset,&type,sizeof(type));
  offset+=sizeof(type);
  memcpy(offset,&size,sizeof(size));
  offset+=sizeof(size);
  memcpy(offset,&data->data()[0],data->length());*/
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
  msg.data->resize(size);
  is.read((char*)msg.data->data(),size);
  return is;
}


// ------------ constructors ----------
// do not forget to encode

void Message::echo(){
  type = T_ECHO;
  data->clear();
  encode();
}

void Message::go_forward(){
  type = T_GO_FORWARD;
  data->clear();
  encode();
}

void Message::go_backward(){
  type = T_GO_BACKWARD;
  data->clear();
  encode();
}

void Message::turn_right(){
  type = T_TURN_RIGHT;
  data->clear();
  encode();
}

void Message::turn_left(){
  type = T_TURN_LEFT;
  data->clear();
  encode();
}

void Message::go_forward_right(){
  type = T_GO_FORWARD_RIGHT;
  data->clear();
  encode();
}

void Message::go_forward_left(){
  type = T_GO_FORWARD_LEFT;
  data->clear();
  encode();
}

void Message::set_speed(int speed){
  type = T_SET_SPEED;
  data->clear();
  data->append(speed);
  encode();
}

void Message::set_degrees(int degrees){
  type = T_ALERT_AT_DEGREES;
  data->clear();
  data->append(degrees);
  encode();
}

void Message::stop(){
  type = T_STOP;
  data->clear();
  encode();
}

void Message::open_claw(){
  type = T_OPEN_CLAW;
  data->clear();
  encode();
}

void Message::close_claw(){
  type = T_CLOSE_CLAW;
  data->clear();
  encode();
}

void Message::change_direction(int direction){
  type = T_CHANGE_DIRECTION;
  data->clear();
  data->append(direction);
  encode();
}

void Message::change_drive_mode(int dm){
  type = T_CHANGE_DRIVE_MODE;
  data->clear();
  data->append(dm);
  encode();
}

void Message::set_pd(int p, int d){
  type = T_SET_PD;

  data->clear();
  data->append(p);
  data->append(d);

  encode();
}

void Message::go_forward_pd(){
  type = T_GO_FORWARD_PD;
  data->clear();
  encode();
}

void Message::calibrate_black(){
  type = T_CALIBRATE_BLACK;
  data->clear();
  encode();
}

void Message::calibrate_white(){
  type = T_CALIBRATE_WHITE;
  data->clear();
  encode();
}
