#include "btinterface.h"

BTInterface::BTInterface(){
  printf("creating bluetooth interface..\n");

#ifdef LINUX
  dev.reset(new QBluetoothLocalDevice);
#endif

  if(is_avaible())
      core->bt_avaible();
  else printf("did not find any local bluetooth devices\n");
}

BTInterface::~BTInterface(){
    printf("destroying bluetooth interface..\n");
}

void BTInterface::connect_to_device(const string &device_address){
#ifdef LINUX
  socket.reset(new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol));
  socket->connectToService(QBluetoothAddress( QString(device_address.c_str())),QBluetoothUuid(QString(REMOTE_SERVICE_UUID)));

  QObject::connect(socket.get(),&QBluetoothSocket::connected,[this](){handle_connected();});
  QObject::connect(socket.get(),&QBluetoothSocket::disconnected,[this](){handle_disconnected();});
  QObject::connect(socket.get(),&QBluetoothSocket::readyRead,[this](){do_read();});
#endif
}

void BTInterface::handle_connected(){
  core->bt_connected();
}

void BTInterface::handle_disconnected(){
  core->bt_disconnected();
}

void BTInterface::do_read(){
  unique_lock<mutex> lck(read_mtx, defer_lock_t());
  if(!lck.try_lock()) return;
  if(!socket_can_be_read()) return;
  printf("reading new message from bluetooth..\n");
  Message::Type_t type = 0;
  Message::Size_t size = 0;
  read_from_socket((char*)&type,sizeof(type));
  read_from_socket((char*)&size,sizeof(size));
#ifdef TEXTMODE
  type-='0';
  size-='0';
#endif
  string data(size,0);

  Message::Size_t bytes_read = read_from_socket((char*)data.data(),size);
  if(bytes_read!=size){
      printf("** could not get all data\n");
      return;
  }
  core->process_new_msg(Msg_ptr(new Message(type,data)));
  do_read();
}

void BTInterface::send(const Msg_ptr& msg){
  unique_lock<mutex> lck(write_mtx);
  write_mgs.emplace_back(msg);
  lck.unlock();
  do_write();
}

void BTInterface::do_write(){
  unique_lock<mutex> lck(write_mtx);
  if(write_mgs.empty() || is_writing) return;
  is_writing = true;
  Msg_ptr msg = write_mgs.front();
  write_mgs.pop_front();
  lck.unlock();
  std::thread t([this,msg](){
    write_to_socket(msg->get_raw_data(),msg->get_raw_data_size());
    unique_lock<mutex> lck(write_mtx);
    is_writing = false;
    lck.unlock();
    do_write();
  });
  t.detach();
}

bool BTInterface::is_avaible(){
#ifdef LINUX
  return dev->isValid();
#endif
  return false;
}

void BTInterface::write_to_socket(char* data, const size_t &size){
#ifdef LINUX
  socket->write(data,size);
#endif
}

size_t BTInterface::read_from_socket(char* data, const size_t &size){
#ifdef LINUX
  return socket->read(data, size);
#endif
  return 0;
}

bool BTInterface::socket_can_be_read(){
#ifdef LINUX
  return socket->bytesAvailable();
#endif
  return false;
}

bool BTInterface::is_connected(){
#ifdef LINUX
    if(!socket.get()) return false;
    return socket->isOpen();
#endif
    return false;
}

void BTInterface::disconnect(){
#ifdef LINUX
    if(!socket.get()) return;
    socket->close();
    socket.reset();
#endif
}
