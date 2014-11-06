#ifndef BTINTERFACE_H
#define BTINTERFACE_H

#include <memory>
#include <mutex>
#include <deque>

//#include <QObject>

#include "glob.h"
#include "core.h"
#include "message.h"

#ifdef LINUX
#include <QtBluetooth>
#endif

class BTInterface {
public:
  BTInterface();
  ~BTInterface();

  void connect_to_device(const string& device_address);
  void send(const Msg_ptr& msg);
  void disconnect();

  bool is_avaible();
  bool is_connected();

private:

  void handle_connected();
  void handle_disconnected();

  void do_read();
  void do_write();

  void write_to_socket(char* data, const size_t& size);
  size_t read_from_socket(char* data, const size_t& size);
  bool socket_can_be_read();

  deque<Msg_ptr> write_mgs;
  bool is_writing = false;
  mutex read_mtx, write_mtx;

#ifdef LINUX
  shared_ptr<QBluetoothLocalDevice> dev;
  shared_ptr<QBluetoothSocket> socket;
#endif

};

#endif // BTINTERFACE_H
