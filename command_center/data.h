#ifndef DATA_H
#define DATA_H
#include "glob.h"

#include <vector>
#include <mutex>
#include <thread>
#include <algorithm>

#ifdef LINUX
#include <boost/thread.hpp>
#endif

#include "message.h"

class Data{    
public:
  Data();
  ~Data();

  void append_msg(const Msg_ptr& msg);
  void rewind();
  bool get_next_msg(Msg_ptr& msg);
  void reset();

  void save(const string& file_name);
  void open(const string& file_name);

  unsigned get_total_msgs();
  unsigned get_current_idx();

private:
  vector<Msg_ptr> msgs;
  unsigned current_msg=0;
  //mutexes
#ifdef LINUX
  typedef boost::shared_mutex rw_mutex;
  typedef boost::shared_lock<boost::shared_mutex> r_lock;
  typedef boost::unique_lock<boost::shared_mutex> w_lock;
#else
  typedef std::mutex rw_mutex;
  typedef std::unique_lock<std::mutex> r_lock;
  typedef std::unique_lock<std::mutex> w_lock;
#endif
  rw_mutex msgs_mtx;
};

#endif // DATA_H
