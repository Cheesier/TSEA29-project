#include "data.h"

Data::Data(){
  printf("creating data..\n");
}

Data::~Data(){
  printf("destroying data..\n");
}

void Data::append_msg(const Msg_ptr &msg){
  w_lock l(msgs_mtx);
  // keep vector sorted
  if(!msgs.empty() && *msgs.back() > *msg){
    //O(n) search does not matter here since inserting in O(n)
    int i = msgs.size()-1;
    for(;i>0 && *msgs[i-1]>*msg; --i);
    msgs.insert(msgs.begin()+i, msg);
    return;
  }
  msgs.emplace_back(msg);
}

unsigned Data::get_total_msgs(){
  r_lock l(msgs_mtx);
  return msgs.size();
}

unsigned Data::get_current_idx(){
  r_lock l(msgs_mtx);
  return current_msg;
}

bool Data::get_next_msg(Msg_ptr &msg){
  w_lock l(msgs_mtx);
  if(current_msg>=msgs.size()) return false;
  msg=msgs[current_msg++];
  return true;
}

void Data::rewind(){
  w_lock l(msgs_mtx);
  current_msg = 0;
}

void Data::reset(){
  w_lock l(msgs_mtx);
  current_msg = 0;
  msgs.clear();
}

void Data::save(const string &file_name){
  r_lock l(msgs_mtx);
  ofstream ofs(file_name);
  for(const Msg_ptr& msg : msgs)
      ofs << *msg;
  ofs.close();
}

void Data::open(const string &file_name){
  w_lock l(msgs_mtx);
  current_msg = 0;
  msgs.clear();
  ifstream f(file_name);
  while(f.peek() != EOF){
    msgs.emplace_back(new Message);
    f >> *msgs.back();
  }
  f.close();
}
