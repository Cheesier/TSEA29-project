#include "message.h"

Message::Message(const Type_t& type_, const string& data_):
    type(type_), data(move(data_)), timestamp(time(0)){}

Message::Type_t Message::get_type(){
  return type;
}

string Message::get_data(){
  return data;
}

time_t Message::get_timestamp(){
  return timestamp;
}

size_t Message::get_data_size(){
  return data.size();
}

void Message::print(){
  printf("type: %d; size:%lu; timestamp:%lu\n%s\n----\n",int(type), data.size(), timestamp,data.c_str());
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

// ------------ constructors ----------
// do not forget to encode

void Message::echo(){
    type = t_echo;
    data = "echo msg";
    encode();
}

void Message::go_forward(){
    type = t_go_forward;
    data.clear();
    encode();
}

void Message::go_backward(){
    type = t_go_backward;
    data.clear();
    encode();
}
void Message::turn_right(){
    type = t_turn_right;
    data.clear();
    encode();
}
void Message::turn_left(){
    type = t_turn_left;
    data.clear();
    encode();
}

void Message::stop(){
    type = t_stop;
    data.clear();
    encode();
}
